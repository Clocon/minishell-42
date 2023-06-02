#include "../include/minishell.h"

static void	ft_getpath(t_pipe *pipex)
{
	char	**path;
	int		i;

	i = 0;
	while (ft_strnstr(pipex->envp[i], "PATH=", 5) == 0)
		i++;
	if (i == ft_sizearray(pipex->envp))
		pipex->path = 0;
	else
	{
		path = ft_calloc(ft_strlen(pipex->envp[i] + 5), sizeof(char));
		if (!path)
			err_msg("PATH_ERROR");
		path = ft_split(pipex->envp[i] + 5, ':');
		pipex->path = path;
	}
}

/* static char	*ft_getcmd(t_pipe pipex, char *cmd)
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
} */

static int	ft_checkquotes(char *input)
{
	char	**quotes;
	int		i;
	int		s;

	i = 0;
	s = 0;
	quotes = ft_split_shell(input, ' ');
	while (quotes[i])
	{
		if (ft_strchr(quotes[i], '\'') || ft_strchr(quotes[i], '"'))
			if (quotes[i][s] != quotes[i][ft_strlen(quotes[i]) - 1]
				|| ft_strlen(quotes[i]) == 1)
			{
				err_msg("Sintax error: ' or \" must be closed\n");
				return (1);
			}
		i++;
	}
	free_matrix(quotes);
	return (0);
}

/* static void	ft_checkredirect(t_pipe *pipex, char **split_pi, t_cmd *cmd)
{
	int		i;
	int		is;
	char	**red;

	i = 0;
	is = 0;
	while (split_pi[i])
	{
		if (ft_strchr(split_pi[i], '<'))
		{

		}
		is = 0;
		i++;
	}
} */

int	ft_countpipe(char *input)
{
	int	i;
	int	npipe;

	i = 0;
	npipe = 0;
	while (input[i])
	{
		ft_foundquotes(input, &i);
		if (input[i] == '|')
			npipe++;
		i++;
	}
	return (npipe);
}

int	ft_checksintaxpipex(char *input)
{
	int		i;
	char	**split;
	char	*aux;

	i = 0;
	split = ft_split_shell(input, '|');
	input = ft_strtrim(input, " ");
	if (ft_countpipe(input) == 0)
		return (0);
	if (ft_countpipe(input) > ft_sizearray(split) || input[0] == '|')
	{
		err_msg("parse error near `|'\n");
		return (1);
	}
	if (ft_countpipe(input) != ft_sizearray(split) - 1)
	{
		if (!split[i])
		{
			err_msg("parse error near `|'\n");
			return (1);
		}
		while (split[i])
		{
			aux = ft_strtrim(split[i], " ");
			if (ft_strlen(aux) == 0)
			{
				err_msg("parse error near `|'\n");
				return (1);
			}
			i++;
		}
	}
	return (0);
}

void	ft_checkinput(char *input, t_pipe *pipex)
{
	int		i;
	char	**split_pi;
	t_cmd	*cmd;

	i = 0;
	if (ft_checkquotes(input) == 0)
	{
		ft_getpath(pipex);
		split_pi = ft_split_shell(input, '|');
		pipex->n_cmd = ft_sizearray(split_pi);
		cmd = malloc(sizeof(t_cmd *) * pipex->n_cmd);
//		ft_checkredirect(pipex, split_pi, &cmd);
		while (split_pi[i])
		{
			printf("INPUT %d = %s\n", i, split_pi[i]);
			i++;
		}
		free_matrix(split_pi);
	}
}
