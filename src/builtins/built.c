#include "../../include/minishell.h"

static void	to_lower(char *str)
{	
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
			str[i] = str[i] + 32;
	}
}

int	builting(t_cmd *cmd)
{
	to_lower(cmd->args[0]);
	if (!ft_strncmp(cmd->args[0], "echo", 5)
		&& !ft_strncmp(cmd->args[1], "-n", 3))
		ft_echo(cmd);
	else
		return (0);
	return (1);
}
