#include "../../include/minishell.h"

static void	to_lower(char *str)
{	
	int	i;
	dprintf(2,"PROBAMOS COSAS EN TOLOWER\n");
	i = -1;
	while (str[++i])
	{
		ft_tolower(str[i]);
	}
}

int	builting(t_cmd *cmd)
{
	to_lower(cmd->args[0]);
	dprintf(2,"PROBAMOS COSAS DESPUES DE TOLOWER\n");
	if (!ft_strncmp(cmd->cmd, "echo", 4)
		&& !ft_strncmp(cmd->args[1], "-n", 2))
		{dprintf(2,"LLORO\n");
		ft_echo(cmd);}
	else
		return (0);
	return (1);
}
