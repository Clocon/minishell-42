#include "../include/minishell.h"


char	*check_trim(char *str)
{
	if (str[0] == '\'')
		str = ft_strtrim(str, "'");
	else if (str[0] == '"')
		str = ft_strtrim(str, "\"");
	return (str);
}

int	redir_check(t_pipe *pipex, t_cmd *cmd, int i)
{
	if (cmd->in_redir == 1)
	{
		pipex->fd_in = open(cmd->infile, O_RDONLY);
		if (pipex->fd_in == -1)
		{
			err_msg("Error al leer archivo\n");
			return (0);
		}
		dup2(pipex->fd_in, 0);
		if (i != pipex->n_cmd - 1)
			pipex->fd_in = pipex->tube[0];
	}
	if (cmd->out_redir == 0)
		return (1);
	if (cmd->out_redir == 1)
		pipex->fd_out = open(cmd->outfile, O_TRUNC | O_CREAT | O_RDWR, 0644);
	else if (cmd->out_redir == 2)
		pipex->fd_out = open(cmd->outfile, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (pipex->fd_out == -1)
		return (0);
	if (i != pipex->n_cmd - 1)
		pipex->fd_out = pipex->tube[1];
	dup2(pipex->fd_out, 1);
	close(pipex->fd_out);
	return (1);
}
