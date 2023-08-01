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

void	ft_getargs(char *one_cmd, t_cmd *cmd)
{
	int		i;
	char	**split_arg;

	i = 0;
	while (one_cmd[i] && one_cmd[i] != '>' && one_cmd[i] != '<')
		i++;
	split_arg = ft_split_shell(ft_substr(one_cmd, 0, i), ' ');
	i = 0;
	cmd->args = malloc((sizeof(char *)) * (ft_sizearray(split_arg) + 1));
	while (split_arg[i] != 0)
	{
		cmd->args[i] = split_arg[i];
		i++;
	}
	cmd->args[i] = 0;
	free(split_arg);
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
	int		i;

	i = 0;
	while (one_cmd[i] && i < ft_strlen(one_cmd))
	{
		ft_foundquotes(one_cmd, &i);
		if (one_cmd[i] != '<' && one_cmd[i] != '>' && i == 0 && one_cmd[i])
		{
			cmd->cmd = ft_getname(&one_cmd[i], &i);
			cmd->cmd = ft_getcmd(*pipex, cmd->cmd);
		}
		else if ((one_cmd[i] == '<' || one_cmd[i] == '>') && one_cmd[i])
			ft_getfiles(cmd, one_cmd, &i, one_cmd[i]);
		i++;
	}
	ft_getargs(one_cmd, cmd);
	/* if (cmd->infile == 2)
		ft_heredoc(); */
}

void	ft_getdatas_nored(t_cmd *cmd, char *one_cmd, t_pipe *pipex)
{
	int		i;
	char	**split_sp;
	char	*clean_quotes;

	i = 0;
	split_sp = ft_split_shell(one_cmd, ' ');
	cmd->cmd = split_sp[0];
	cmd->cmd = ft_getcmd(*pipex, cmd->cmd);
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
	cmd->infile_redirect = 0;
	cmd->outfile_redirect = 0;
	cmd->infile = 0;
	cmd->outfile = 0;
	while (i < pipex->n_cmd)
	{
		if (ft_existred(split_pi[i]) == 0)
			ft_getdatas_nored(&cmd[i], split_pi[i], pipex);
		else
			ft_getdatas_red(&cmd[i], split_pi[i], pipex);
		i++;
	}
	free_matrix(split_pi);
//	ft_expandvalues(cmd, pipex);
	i = 0;
 	printf("ncmd = %D\n", pipex->n_cmd);
	while (i < pipex->n_cmd)
	{
		//(cmd[i]).cmd = ft_expandit((cmd[i]).cmd, pipex, 0);
		printf("\n\n---* CMD = %s *---\n", (cmd[i]).cmd);
		i_s = 0;
		while ((cmd[i]).args[i_s])
		{
			//(cmd[i]).args[i_s] = ft_expandit((cmd[i]).args[i_s], pipex, 0);
			printf("---* Args_%s = %s *---\n", (cmd[i]).cmd, (cmd[i]).args[i_s]);
			i_s++;
		}
		//(cmd[i]).infile = ft_expandit((cmd[i]).infile, pipex, 0);
		printf(">Infile_name = %s\n", (cmd[i]).infile);
		//(cmd[i]).outfile = ft_expandit((cmd[i]).outfile, pipex, 0);
		printf("<Outfile_name = %s\n", (cmd[i]).outfile);
		i++;
	}
	return (cmd);
}
