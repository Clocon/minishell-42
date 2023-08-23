#include "../../include/minishell.h"

void	ft_heredoc(t_cmd *cmd)
{
	int		tmp_fd;
	char	*input;

	tmp_fd = open(HEREDOC_FILE, O_TRUNC | O_CREAT | O_RDWR, 0644);
	input = readline("> ");
	while (ft_strncmp(input, cmd->infile, ft_strlen(cmd->infile) + 1))
	{
		write(tmp_fd, input, ft_strlen(input));
		write(tmp_fd, "\n", 1);
		input = readline("> ");
	}
	close(tmp_fd);
	free(cmd->infile);
	cmd->infile = HEREDOC_FILE;
}

char	*ft_getname(char *cmd, int *j)
{
	int		i;
	char	*name;

	i = 0;
	while (cmd[i] && cmd[i] != ' ' && cmd[i] != '<' && cmd[i] != '>')
	{
		ft_foundquotes(&cmd[i], &i);
		i++;
	}
	i--;
	name = ft_substr(cmd, 0, i + 1);
	name[i + 1] = 0;
	*j += i;
	if (name[0] == '\'')
		name = ft_strtrim(name, "'");
	else if (name[0] == '"')
		name = ft_strtrim(name, "\"");
	return (name);
}

void	ft_getfiles(t_cmd *cmd, char *str, int *i, int red)
{
	if (red == '>')
		cmd->outfile_redirect = 1;
	else if (red == '<')
		cmd->infile_redirect = 1;
	*i += 1;
	while (str[*i] == '>' || str[*i] == '<' || str[*i] == ' ')
	{
		if (str[*i] == '>' && red == '>')
			cmd->outfile_redirect = 2;
		else if (str[*i] == '<' && red == '<')
			cmd->infile_redirect = 2;
		*i += 1;
	}
	if (red == '>')
		cmd->outfile = ft_getname(&str[*i], i);
	else if (red == '<')
		cmd->infile = ft_getname(&str[*i], i);
}

void	ft_getdatas_red(t_cmd *cmd, char *one_cmd, t_pipe *pipex)
{
	int			i;
	t_typetoken	type;

	i = 0;
	type = WORD;
	while (one_cmd[i])
	{
		if (one_cmd[i] == '>')
		{
			cmd->outfile_redirect = 1;
			if (type == RED_OUT)
			{
				cmd->outfile_redirect = 2;
				type = RED_APPEND;
			}
			else
				type = RED_OUT;
		}
		else if (one_cmd[i] == '<')
		{
			cmd->infile_redirect = 1;
			if (type == RED_IN)
			{
				//cmd->infile_redirect = 2;
				type = RED_HERE;
			}
			else
				type = RED_IN;
		}
		else if (one_cmd[i] != ' ' && one_cmd[i] != '\t')
		{
			if (type == RED_IN || type == RED_HERE)
			{
				if (cmd->infile && type == RED_IN)
					free(cmd->infile);
				cmd->infile = ft_getname(&one_cmd[i], &i);
				if (type == RED_HERE)
					ft_heredoc(cmd);
			}
			else if (type == RED_OUT || type == RED_APPEND)
			{
				if (!cmd->outfile)
				{
					cmd->outfile = ft_getname(&one_cmd[i], &i);
				}
				else
				{
					close(open(cmd->outfile, O_CREAT | O_RDWR | O_TRUNC, 0644));
					free(cmd->outfile);
					cmd->outfile = ft_getname(&one_cmd[i], &i);
				}
			}
			else if (!cmd->cmd)
			{
				cmd->cmd = ft_getname(&one_cmd[i], &i);
				cmd->args = ft_addarray(cmd->cmd, cmd->args);
				cmd->cmd = ft_getcmd(*pipex, cmd->cmd);
			}
			else
				cmd->args = ft_addarray(ft_getname(&one_cmd[i], &i), cmd->args);
			type = WORD;
		}
		i++;
	}
}

static	char	*ft_cleanquotes(char *input)
{
	char	*str;

	str = NULL;
	if (input[0] == '\'')
		str = ft_strtrim(input, "'");
	else if (input[0] == '"')
		str = ft_strtrim(input, "\"");
	else
		str = ft_strdup(input);
	return (str);
}

void	ft_getdatas_nored(t_cmd *cmd, char *one_cmd, t_pipe *pipex)
{
	int		i;
	char	**split_sp;
	char	*clean_quotes;

	i = 0;
	split_sp = ft_split_shell(one_cmd, ' ');
	clean_quotes = ft_cleanquotes(split_sp[0]);
	if (clean_quotes)
	{
		cmd->cmd = ft_strdup(ft_getcmd(*pipex, clean_quotes));
		cmd->args = malloc((sizeof(char *)) * (ft_sizearray(split_sp) + 1));
		while (split_sp[i] != 0)
		{
			cmd->args[i] = ft_cleanquotes(split_sp[i]);
			free(split_sp[i]);
			i++;
		}
		cmd->args[i] = 0;
	}
	free(split_sp);
	free(clean_quotes);
}

t_cmd	*ft_getinput(char *input, t_pipe *pipex, t_cmd *cmd)
{
	int		i;
	int		i_s;
	char	**split_pi;

	i = 0;
	i_s = 0;
	split_pi = ft_split_shell(input, '|');
	split_pi = ft_cleanspaces(split_pi);
	cmd = malloc(sizeof(t_cmd) * pipex->n_cmd);
	while (i < pipex->n_cmd)
	{
		cmd[i].infile_redirect = 0;
		cmd[i].outfile_redirect = 0;
		cmd[i].infile = NULL;
		cmd[i].outfile = NULL;
		cmd[i].args = NULL;
		cmd[i].cmd = NULL;
		if (ft_existred(split_pi[i]) == 0)
			ft_getdatas_nored(&cmd[i], split_pi[i], pipex);
		else
			ft_getdatas_red(&cmd[i], split_pi[i], pipex);
		i++;
	}
	free_matrix(split_pi);
	return (cmd);
}



/*     	i = 0;
 	printf("ncmd = %D\n", pipex->n_cmd);
	 while (i < pipex->n_cmd)
	{
		printf("\n\n---* CMD = %s *---\n", (cmd[i]).cmd);
		i_s = 0;
		while ((cmd[i]).args && (cmd[i]).args[i_s])
		{
			printf("---* Args_%s = %s *---\n", (cmd[i]).cmd, (cmd[i]).args[i_s]);
			i_s++;
		}
		printf(">Infile_name = %s\n", (cmd[i]).infile);
		printf("<Outfile_name = %s\n", (cmd[i]).outfile);
		i++;
	}*/