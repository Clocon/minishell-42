#include "../../include/minishell.h"

// static char	*ft_getenv(char *env, t_pipe *pipex, int start, int size)
// {
// 	int		i;
// 	char	*aux;

// 	i = 0;
// 	while (pipex->envp[i])
// 	{
// 		aux = ft_strchr(pipex->envp[i], '=') + 1;
// 		if (size == aux - pipex->envp[i] - 1)
// 			if (ft_strncmp(&env[start], pipex->envp[i], size - 2) == 0)
// 				return (ft_strdup(aux));
// 		i++;
// 	}
// 	return (ft_strdup(""));
// }
//// VER ESTA FUNCION DE ARRIBA CON JESSICA ////

/* static void	ft_cd_newpwd(t_pipe *pipex)
{
	int		i;
	char	*aux;

	i = 0;
	while (ft_strncmp(pipex->envp[i], "PWD=", 4) != 0)
		i++;
	if (pipex->envp[i + 1])
	{
		free(pipex->envp[i + 1]);
		pipex->envp[i + 1] = ft_strdup(pipex->envp[i]);
	}
	free(pipex->envp[i]);
	if (getcwd(aux, 2048) == 0)
		return (err_msg("PWD"));
}

void	ft_cd(t_pipe *pipex, t_cmd *cmd)
{
	char	*aux;

	if (!cmd->args[1])
	{
		aux = ft_getenv()
	}
} */

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
	// else
	// 	ft_setenv("OLDPWD", old_path, pipex);

	//addarray("OLDPWD=old_path", pipex->envp);
	//deletearray!!!
}
