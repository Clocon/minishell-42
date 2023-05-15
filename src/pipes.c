#include "../include/minishell.h"

static void	child(t_cmd *cmd, char **envp)
{
	dprintf(2, "Soy el comando == %s\n", cmd->cmd);
	if (!cmd->cmd)
	{
		free_matrix(cmd->args);
		free(cmd->cmd);
		err_msg_exit(CMD_ERROR);
//		exit(1);
	}
	check_awk(cmd);
	execve(cmd->cmd, cmd->args, envp);
}
#include <signal.h>
void	child_generator(t_pipe *pipex, t_cmd *cmd, int n_cmd, char **envp)
{
	int		i;
	pid_t	pid[3];
	int		to_wait;
	int		tube[2];

	i = -1;
	while (++i < n_cmd)
	{
		//dprintf(2, "creo el hijo nº = %d\n", i);
		dup2(pipex->fd_in, 0);
		close(pipex->fd_in);
		if (i != n_cmd - 1)
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
		pid[i] = fork();
		//dprintf(2, "PID = %d\n", pid[i]);
		if (!pid[i])
			child(&cmd[i], envp);
		//printf("ME VOY!! == %s\n", cmd->cmd);
		free_matrix(cmd[i].args);
		//kill(pid[i], 0);
	}
	waitpid(-1, &to_wait, 0);
	//	if (i == n_cmd - 1)
	//waitpid(pid, &to_wait, 0);
	//printf("SALÍ WEY!\n");
	free(cmd);
}
