#include "../../include/minishell.h"

static void	to_lower(char *str)
{	
	int	i;

	i = -1;
	while (str[++i])
	{
		ft_tolower(str[i]);
	}
}

int	builting(t_cmd *cmd, t_pipe *pipex)
{
	to_lower(cmd->args[0]);
	if (!ft_strncmp(cmd->args[0], "echo", 5)
		&& !ft_strncmp(cmd->args[1], "-n", 3))
		ft_echo(cmd);
	else if (!ft_strncmp(cmd->args[0], "pwd", 4))
		ft_pwd();
	else if (!ft_strncmp(cmd->args[0], "cd", 3))
		ft_cd(cmd, pipex);
	else
		return (0);
	return (1);
}
