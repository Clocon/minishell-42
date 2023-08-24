#include "../../include/minishell.h"

/**
 * @brief Built-in unset: elimina de las variables de entorno 
 * la variable que se le indique por argumentos. 
 * 
 * @param cmd struct con el comando y su argumento
 * @param pipex struct con las variables de entorno
 */
void	ft_unset(t_cmd *cmd, t_pipe *pipex)
{
	int		pos;

	if (cmd->args[1])
	{
		pos = ft_foundenv(cmd->args[1], pipex->envp);
		if (pos >= 0)
			pipex->envp = ft_deleteitem(pos, pipex->envp);
	}
}
