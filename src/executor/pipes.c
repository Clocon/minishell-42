#include "../../include/minishell.h"

extern int errno;

static void	child(t_cmd *cmd, t_pipe *pipex)
{
	char	*error;

	error = NULL;
	if (!cmd->cmd)
	{
		free_matrix(cmd->args);
		free(cmd->cmd);
		err_msg_exit(CMD_ERROR);
	}
	//check_awk(cmd);
	if (execve(cmd->cmd, cmd->args, pipex->envp) == -1)
	{
		error = ft_strjoin_free(cmd->cmd, ": ");
		error = ft_strjoin_free(error, CMD_ERROR);
		pipex->shell_exit = 127;
		err_msg(error);
	}
	exit (pipex->shell_exit);
}

static void	dup_assignation(t_pipe *pipex, t_cmd *cmd, int i)
{
	if (cmd->infile_redirect == 0)
	{
		dup2(pipex->fd_in, 0);
	}
	if (i != pipex->n_cmd - 1)
	{
		if (pipe(pipex->tube) == -1)
			err_msg(PIPE_ERROR);
		if (cmd->infile_redirect == 0)
			pipex->fd_in = pipex->tube[0];
		if (cmd->outfile_redirect == 0)
			pipex->fd_out = pipex->tube[1];
	}
	else if (cmd->outfile_redirect == 0)
		pipex->fd_out = dup(pipex->tmp_out);
	if (cmd->outfile_redirect == 0)
	{
		dup2(pipex->fd_out, 1);
		close(pipex->fd_out);
	}
}

void	child_generator(t_pipe *pipex, t_cmd *cmd)
{
	int		i;
	pid_t	pid;
	int		to_wait;
	int		keyboard_fd;
	int		display_fd;

	keyboard_fd = dup(0);
	display_fd = dup(1);
	i = -1;
	while (++i < pipex->n_cmd)
	{		
		dup_assignation(pipex, &cmd[i], i);
		if (cmd[i].infile_redirect != 0 || cmd[i].outfile_redirect != 0)
			if (!redir_check(pipex, &cmd[i], i))
				break ;
		if (builting(&cmd[i], pipex))
			continue ;
/* 		else
		{ */
			pid = fork();
			if (!pid)
				child(&cmd[i], pipex);
			waitpid(pid, &to_wait, 0);
			pipex->shell_exit = WEXITSTATUS(to_wait);
/* 		} */
		//free_matrix(cmd[i].args);
	}
	//free(cmd);
	dup2(keyboard_fd, 0);
	close(keyboard_fd);
	dup2(display_fd, 1);
	close(display_fd);
	//pipex->shell_exit = 0;
}
