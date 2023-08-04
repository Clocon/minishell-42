#include "../../include/minishell.h"

void	ft_echo(t_cmd *cmd)
{
	int	j;

	j = 1;
	if (cmd->args[1] && ft_strncmp(cmd->args[1], "-n", 3) == 0)
		j++;
	while (cmd->args[j])
	{
		ft_putstr_fd(cmd->args[j++], 1);
		if (cmd->args[j])
			ft_putstr_fd(" ", 1);
	}

	if (!(cmd->args[1] && ft_strncmp(cmd->args[1], "-n", 3) == 0))
		ft_putstr_fd("\n", 1);
}
