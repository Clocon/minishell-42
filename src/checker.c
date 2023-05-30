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
	quotes = ft_splitpipex(input, ' ');
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
	free(quotes);
	return (0);
}

void	ft_checkinput(char *input, t_pipe *pipex)
{
	int		i;
	char	**split_pi;

	i = 0;
	if (ft_checkquotes(input) == 0)
	{
		ft_getpath(pipex);
		split_pi = ft_splitpipex(input, '|');
/* 		cmd = malloc(sizeof(t_cmd));
		if (!cmd)
			err_msg_exit("Error de memoria:"); */
		while (split_pi[i])
			{
			//ft_checkredirect(split_pi[i]);
			printf("INPUT %d = %s\n", i, split_pi[i]);
			i++;
		}
		//err_msg("saludos");
	}
}
