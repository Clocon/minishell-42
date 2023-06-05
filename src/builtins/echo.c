#include "../../include/minishell.h"

void	ft_echo(t_cmd *cmd)
{
	int	len;
	int	i;
	int	j;

	j = 1;
	while (cmd->args[++j])
	{
		cmd->args[j] = check_trim(cmd->args[j]);
		len = ft_strlen(cmd->args[j]);
		i = -1;
		while (++i < len)
		{
			dprintf(2,"%c\n", cmd->args[j][i]);
			if (!cmd->args[j][i + 1])
				if (cmd->args[j][len - 1] == '\n' && i == len -1)
					break ;
			ft_putchar_fd(cmd->args[j][i], 1);
		}
	}
}
