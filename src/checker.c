#include "../include/minishell.h"

static void	ft_getpath(t_pipe *pipex)
{
	char	**path;
	int		i;

	i = 0;
	while (ft_strnstr(pipex->envp[i], "PATH=", 5) == 0)
		i++;
	path = ft_calloc(ft_strlen(pipex->envp[i] + 5), sizeof(char));
	if (!path)
		err_msg("PATH_ERROR");
	path = ft_split(pipex->envp[i] + 5, ':');
	pipex->path = path;
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
	return (NULL);
} */

void	ft_checkinput(char *input, t_pipe *pipex)
{
	int		i;
	char	**split_in;

	i = 0;
	ft_getpath(pipex);
	split_in = ft_split_shell(input, ' ');
	while (split_in[i])
	{
		printf("INPUT %d = %s\n", i, split_in[i]);
		i++;
	}
}
