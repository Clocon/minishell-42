#include "../../include/minishell.h"

void	ft_unset(t_cmd *cmd, t_pipe *pipex)
{
	int		pos;
	int		i;

	i = 0;
	if (cmd->args[1])
	{
		pos = ft_foundenv(cmd->args[1], pipex->envp);
		if (pos >= 0)
			pipex->envp = ft_deleteitem(pos, pipex->envp);
	}
}
