#include "../include/minishell.h"


/* static void	fd_assigned(t_pipe *pipex, int n_cmd)
{
	int	i;

	i = 0;
	while (++i < n_cmd)
	{
		pipex[i].tube[0] = pipex[i].fd_in;
		pipex[i].tube[1] = pipex[i].fd_out;
	}
} */

static void	child(t_cmd *cmd, char **envp)
{
		if (!cmd->cmd)
		{
			//free_matrix(pipex.args);
			//free(pipex.cmd);
			err_msg(CMD_ERROR);
			//exit(1);
		}
		//check_awk(&pipex);
		execve(cmd->cmd, cmd->args, envp);
}

/* static void	close_pipes(t_pipe *pipex, int n_cmd)
{
	int	i;

	i = -1;
	while (++i < n_cmd)
	{
		close(pipex[i].tube[0]);
		close(pipex[i].tube[1]);
	}
} */

void	child_generator(t_pipe *pipex, t_cmd *cmd, int n_cmd, char **envp)
{
	int	i;
	int	pid;
	//int to_wait;
	int	tube[2];
	//fd_assigned(pipex, n_cmd);
	i = -1;
	while (++i < n_cmd)
	{
		printf("concha? == %s...%d\n", cmd[i].cmd, i);
		dup2(pipex->fd_in, 0);
		close(pipex->fd_in);
		if (i != n_cmd -1)
		{
			if (pipe(tube) == -1)
				err_msg(PIPE_ERROR);
			pipex->fd_in = tube[0];
			pipex->fd_out = tube[1];
		}
		else
			pipex->fd_out = dup(pipex->tmp_out);
		dup2(pipex->fd_out, 1);
		close(pipex->fd_out);
		pid = fork();
		if (!pid)
			child(&cmd[i], envp);
		free_matrix(cmd[i].args);
/* 		if (i == n_cmd -1)
			waitpid(pid, &to_wait, 0); */
	}
	free(cmd);
	//free_arr_int(pipex);
}
