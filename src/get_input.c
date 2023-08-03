#include "../include/minishell.h"

static char	*ft_getcmd(t_pipe pipex, char *cmd)
{
	int		i;
	char	*aux;
	char	*c;
	char	*ex;

	i = 0;
	while (cmd[i] != 0 && cmd[i] != ' ')
		i++;
	ex = ft_substr(cmd, 0, i);
	i = 0;
	if (access(ex, X_OK) == 0)
		return (ex);
	while (pipex.path[i])
	{
		aux = ft_strjoin(pipex.path[i], "/");
		c = ft_strjoin(aux, ex);
		free (aux);
		if (access(c, X_OK) == 0)
			return (c);
		free (c);
		i++;
	}
	return (cmd);
}

void	ft_addarg(char *arg, t_cmd *cmd)
{
	char	**new_arg;
	int		i;

	if (!cmd->args)
	{
		cmd->args = ft_calloc(sizeof(char *), 2);
		cmd->args[0] = arg;
	}
	else
	{
		new_arg = ft_calloc(sizeof(char *), ft_sizearray(cmd->args) + 2);
		i = -1;
		while (cmd->args[++i])
			new_arg[i] = ft_strdup(cmd->args[i]);
		new_arg[i] = arg;
		free_matrix(cmd->args);
		cmd->args = new_arg;
	}
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
				cmd->infile_redirect = 1;
				type = RED_HERE;
			}
			else
				type = RED_IN;
		}
		else if (one_cmd[i] != ' ' && one_cmd[i] != '\t')
		{
			if (type == RED_IN || type == RED_HERE)
			{
				if (cmd->infile)
					free(cmd->infile);
				cmd->infile = ft_getname(&one_cmd[i], &i);
			}
			else if (type == RED_OUT || type == RED_APPEND)
			{
				if (!cmd->outfile)
				{
					cmd->outfile = ft_getname(&one_cmd[i], &i);
					close(open(cmd->outfile, O_CREAT | O_RDWR, 0644));
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
				ft_addarg(cmd->cmd, cmd);
				cmd->cmd = ft_getcmd(*pipex, cmd->cmd);
			}
			else
				ft_addarg(ft_getname(&one_cmd[i], &i), cmd);
			type = WORD;
		}
		i++;
	}
/*	if (cmd->infile == 2)
		ft_heredoc(); */
}

void	ft_getdatas_nored(t_cmd *cmd, char *one_cmd, t_pipe *pipex)
{
	int		i;
	char	**split_sp;
	char	*clean_quotes;

	i = 0;
	split_sp = ft_split_shell(one_cmd, ' ');
	if (split_sp[0][0] == '\'')
		clean_quotes = ft_strtrim(split_sp[0], "'");
	else if (split_sp[0][0] == '"')
		clean_quotes = ft_strtrim(split_sp[0], "\"");
	else
		clean_quotes = ft_strdup(split_sp[0]);
	cmd->cmd = clean_quotes;
	cmd->cmd = ft_strdup(ft_getcmd(*pipex, cmd->cmd));
	cmd->args = malloc((sizeof(char *)) * (ft_sizearray(split_sp) + 1));
	while (split_sp[i] != 0)
	{
		if (split_sp[i][0] == '\'')
			clean_quotes = ft_strtrim(split_sp[i], "'");
		else if (split_sp[i][0] == '"')
			clean_quotes = ft_strtrim(split_sp[i], "\"");
		else
			clean_quotes = ft_strdup(split_sp[i]);
		free(split_sp[i]);
		cmd->args[i] = clean_quotes;
		i++;
	}
	cmd->args[i] = 0;
	free(split_sp);
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
 /* 	i = 0;
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
	} */
	return (cmd);
}
