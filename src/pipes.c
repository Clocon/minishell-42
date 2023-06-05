#include "../include/minishell.h"

static void	child(t_cmd *cmd, t_pipe *pipex)
{
	if (!cmd->cmd)
	{
		free_matrix(cmd->args);
		free(cmd->cmd);
		err_msg_exit(CMD_ERROR);
	}
	//check_awk(cmd);
	execve(cmd->cmd, cmd->args, pipex->envp);
	exit (0);
}

static void	dup_assignation(t_pipe *pipex, t_cmd *cmd, int i)
{
	if (cmd->in_redir == 0)
	{
		dup2(pipex->fd_in, 0);
	}
	if (i != pipex->n_cmd - 1)
	{
		if (pipe(pipex->tube) == -1)
			err_msg(PIPE_ERROR);
		if (cmd->in_redir == 0)
			pipex->fd_in = pipex->tube[0];
		if (cmd->out_redir == 0)
			pipex->fd_out = pipex->tube[1];
	}
	else if (cmd->out_redir == 0)
		pipex->fd_out = dup(pipex->tmp_out);
	if (cmd->out_redir == 0)
	{
		dup2(pipex->fd_out, 1);
		close(pipex->fd_out);
	}
}

void	child_generator(t_pipe *pipex, t_cmd *cmd)
{
	int		i;
	pid_t	pid[3];
	int		to_wait;

	i = -1;
	while (++i < pipex->n_cmd)
	{
		dup_assignation(pipex, cmd, i);
		if (cmd[i].in_redir != 0 || cmd[i].out_redir != 0)
			redir_check(pipex, &cmd[i], i);
	dprintf(2,"Peta aqui? Valor de I = %d --- con CMD = %s\n", i, cmd[i].cmd);
		if (builting(&cmd[i]))
			continue ;
/* 		else
		{ */
			pid[i] = fork();
			if (!pid[i])
				child(&cmd[i], pipex);
			waitpid(pid[i], &to_wait, 0);
/* 		} */
		//free_matrix(cmd[i].args);
	}
	//free(cmd);
	fd_comeback();
}
