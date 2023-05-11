#include "../include/minishell.h"

void	sub_dup2(int zero, int one)
{
	printf("Empiezo sub_Dup!\n");
	dup2(zero, 0);
	dup2(one, 1);
	printf("termino\n");
}

/* void	check_awk(t_pipe *pipex)
{
	if (ft_strncmp(pipex->args[0], "awk", 3) == 0)
	{	
		if (pipex->args[1][0] == '\'')
			pipex->args[1] = ft_strtrim(pipex->args[1], "'");
		else if (pipex->args[1][0] == '"')
			pipex->args[1] = ft_strtrim(pipex->args[1], "\"");
	}
} */

/* int	**pipes_generator(int n_cmd)
{
	int	i;
	int	**tube;

	tube = (int **)malloc(sizeof(int *) * (n_cmd - 1));
	if (!tube)
		err_msg_exit(PIPE_ERROR);
	i = -1;
	while (++i < n_cmd - 1)
	{
		tube[i] = (int *)malloc(sizeof(int) * 2);
		if (!tube[i])
			err_msg_exit(PIPE_ERROR);
	}
	i = -1;
	while (++i < n_cmd - 1)
	{
		if (pipe(tube[i]) < 0)
			err_msg_exit(PIPE_ERROR);
	}
	return (tube);
}
 */