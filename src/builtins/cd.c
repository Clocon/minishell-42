/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmerchan <jmerchan@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 16:22:33 by jmerchan          #+#    #+#             */
/*   Updated: 2023/09/07 16:22:34 by jmerchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Built-in cd: que cambia de directorio, admite las opciones
 * cd (NULL) para volver a la raíz, cd .. para subir de carpeta
 * cd - para ir al directorio anterior y cd con la ruta 
 * 
 * @param cmd struct con el comando y los argumentos
 * @param pipex struct con las variables de entorno
 */
void	ft_cd(t_cmd *cmd, t_pipe *pipex)
{
	char	*error;
	char	*path;
	char	*old_path;

	error = NULL;
	path = cmd->args[1];
	old_path = getcwd(NULL, 0);
	if (!path)
		path = ft_getenv("HOME", pipex);
	else if (ft_strncmp(path, "-", 2) == 0)
		path = ft_getenv("OLDPWD", pipex);
	if (chdir(path))
	{
		error = ft_strjoin("cd: ", cmd->args[1]);
		error = ft_strjoin_free(error, ": No such file or directory\n");
		err_msg(error);
		free(error);
	}
	else
	{
		pipex->envp = ft_deleteitem(\
		ft_foundenv("OLDPWD", pipex->envp), pipex->envp);
		old_path = ft_strjoin("OLDPWD=", old_path);
		pipex->envp = ft_addarray(old_path, pipex->envp);
	}
}
