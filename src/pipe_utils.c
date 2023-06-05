#include "../include/minishell.h"

void	fd_comeback(void)
{
	int		keyboard_fd;
	int		display_fd;

	keyboard_fd = dup(0);
	display_fd = dup(1);
	dup2(keyboard_fd, 0);
	close(keyboard_fd);
	dup2(display_fd, 1);
	close(display_fd);
}

char	*check_trim(char *str)
{
	if (str[0] == '\'')
		str = ft_strtrim(str, "'");
	else if (str[0] == '"')
		str = ft_strtrim(str, "\"");
	return (str);
}

void	redir_check(t_pipe *pipex, t_cmd *cmd, int i)
{
	if (cmd->in_redir == 1)
	{
		pipex->fd_in = open(cmd->infile, O_RDONLY);
		if (pipex->fd_in == -1)
		{
			err_msg("Error al leer archivo\n");
			fd_comeback();
		}
		else
			dup2(pipex->fd_in, 0);
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
