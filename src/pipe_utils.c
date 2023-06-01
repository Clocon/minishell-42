#include "../include/minishell.h"

void	check_awk(t_cmd *cmd)
{
	if (ft_strncmp(cmd->args[0], "awk", 3) == 0)
	{	
		if (cmd->args[1][0] == '\'')
			cmd->args[1] = ft_strtrim(cmd->args[1], "'");
		else if (cmd->args[1][0] == '"')
			cmd->args[1] = ft_strtrim(cmd->args[1], "\"");
	}
}

void	redir_check(t_pipe *pipex, t_cmd *cmd, int i)
{
	if (cmd->in_redir == 1)
	{
		pipex->fd_in = open(cmd->infile, O_RDONLY);
		if (pipex->fd_in == -1)
			err_msg_exit("Error al leer archivo\n");
		dup2(pipex->fd_in, 0);
		//close(pipex->fd_in);
		if (i != pipex->n_cmd - 1)
			pipex->fd_in = pipex->tube[0];
	}
	if (cmd->out_redir == 0)
		return ;
	if (cmd->out_redir == 1)
		pipex->fd_out = open(cmd->outfile, O_TRUNC | O_CREAT | O_RDWR, 0644);
	if (cmd->out_redir == 2)
		pipex->fd_out = open(cmd->outfile, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (i != pipex->n_cmd - 1)
		pipex->fd_out = pipex->tube[1];
	dup2(pipex->fd_out, 1);
	close(pipex->fd_out);
}
