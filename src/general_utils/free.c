#include "../../include/minishell.h"

void	free_matrix(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	close_pipes(int *tube)
{
	close(tube[0]);
	close(tube[1]);
}

void	clean_success(t_pipe *pipe)
{
	(void)pipe;
	//free_matrix(pipe->envp);
	exit(0);
}
