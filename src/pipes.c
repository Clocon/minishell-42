#include "../include/minishell.h"


static void	fd_assigned(t_pipe *pipex, int n_cmd)
{
	int	i;

	i = 0;
	while (++i < n_cmd)
	{
		pipex[i].tube[0] = pipex[i].fd_in;
		pipex[i].tube[1] = pipex[i].fd_out;
	}
	
}

void	child(t_pipe pipex, char **envp)
{
	int	pid;

	pid = fork();

	printf("CMD == %s!\n", pipex.cmd);
	sub_dup2(pipex.tube[0], pipex.tube[1]);
	if (!pid)
	{
		//close_pipes(&pipex);
		if (!pipex.cmd)
		{
			//free_matrix(pipex.args);
			//free(pipex.cmd);
			err_msg(CMD_ERROR);
			//exit(1);
		}
		check_awk(&pipex);
		execve(pipex.cmd, pipex.args, envp);
	}
}

void	child_generator(t_pipe *pipex, int n_cmd, char **envp)
{
	int		i;

	fd_assigned(pipex, n_cmd);
	i = -1;
	while (++i < n_cmd - 1)
		child(pipex[i], envp);
	//free_arr_int(pipex);
}
