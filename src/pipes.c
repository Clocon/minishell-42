#include "../include/minishell.h"

static void	child(t_cmd *cmd, t_pipe *pipex)
{
	if (!cmd->cmd)
	{
		free_matrix(cmd->args);
		free(cmd->cmd);
		err_msg_exit(CMD_ERROR);
	}
	check_awk(cmd);
	execve(cmd->cmd, cmd->args, pipex->envp);
}

static void	dup_assignation(t_pipe *pipex, int i)
{
	int	tube[2];

	dup2(pipex->fd_in, 0);
	close(pipex->fd_in);
	if (i != pipex->n_cmd - 1)
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
}

void	child_generator(t_pipe *pipex, t_cmd *cmd)
{
	int		i;
	pid_t	pid[3];
	int		to_wait;
	int		keyboard_fd;

	keyboard_fd = dup(0);
	i = -1;
	while (++i < pipex->n_cmd)
	{
		dup_assignation(pipex, i);
		pid[i] = fork();
		if (!pid[i])
			child(&cmd[i], pipex);
		waitpid(pid[i], &to_wait, 0);
		free_matrix(cmd[i].args);
	}
	free(cmd);
	dup2(keyboard_fd, 0);
}
