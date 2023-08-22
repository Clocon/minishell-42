#include "../../include/minishell.h"

void	ft_exit(t_cmd *cmd)
{
	if (cmd->args[2])
		err_msg("exit: too many arguments\n");
	else
	{
		if (cmd->args[1])
			exit(ft_atoi(cmd->args[1]));
		exit(0);
	}
}
