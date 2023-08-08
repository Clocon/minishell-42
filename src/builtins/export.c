#include "../../include/minishell.h"

/**
 * @brief Built-in export: exporta a las variables de entorno (pipex)
 * la variable que se indique como parámetro.
 * 
 * @param cmd struct con el comando y sus argumentos
 * @param pipex structu con las variables de entorno
 */
void	ft_export(t_cmd *cmd, t_pipe *pipex)
{
	int		pos;
	char	*var_name;
	int		i;

	i = 0;
	if (cmd->args[1] && ft_strchr(cmd->args[1], '='))
	{
		while (cmd->args[1][i] && cmd->args[1][i] != '=')
			i++;
		var_name = ft_substr(cmd->args[1], 0, i);
		pos = ft_foundenv(var_name, pipex->envp);
		if (pos < 0)
			pipex->envp = ft_addarray(cmd->args[1], pipex->envp);
		else
		{
			pipex->envp = ft_deleteitem(pos, pipex->envp);
			pipex->envp = ft_addarray(cmd->args[1], pipex->envp);
		}
	}
}
