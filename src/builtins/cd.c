#include "../../include/minishell.h"

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
