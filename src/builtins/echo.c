#include "../../include/minishell.h"

void	ft_echo(t_cmd *cmd)
{
	int	len;
	int	i;
	int	j;

	j = 1;
	while (cmd->args[++j])
	{
		len = ft_strlen(cmd->args[j]);
		i = 0;
		while (++i < len)
		{
			if (!cmd->args[j][i + 1])
				if (cmd->args[j][len - 1] == '\n' && i == len -1)
					break ;
			printf("%c", cmd->args[j][i]);
		}
	}
}
