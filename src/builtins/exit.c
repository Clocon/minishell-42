#include "../../include/minishell.h"

/**
 * @brief Builtin 'exit', sale de la minishell. Sale con el valor 
 * que se le indique por argumentos. Si no se indica, sale con 0. 
 * 
 * @param cmd estructura con el comando
 */
void	ft_exit(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (cmd->args[1] && cmd->args[2])
		err_msg("exit: too many arguments\n");
	else
	{
		if (cmd->args[1])
		{
			while (cmd->args[1][i])
			{
				if (!ft_isdigit(cmd->args[1][i]))
				{
					err_msg("exit: numeric argument required: ");
					ft_putstr_fd(cmd->args[1], 2);
					ft_putstr_fd("\n", 2);
					return ;
				}
				i++;
			}
			exit(ft_atoi(cmd->args[1]));
		}
		exit(0);
	}
}
