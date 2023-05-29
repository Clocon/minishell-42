#include "../include/minishell.h"

void	free_matrix(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	close_pipes(int *tube)
{
	close(tube[0]);
	close(tube[1]);
}
void	clean_commands(t_cmd *cmd)
{
	int	i;

	i = -1;
	while (++i < cmd->n_commands)
	{
		ft_split_free(cmd->cmd[i].opt);
		free_matrix((void **)&cmd->cmd[i].path);
		free_matrix((void **)&cmd->cmd[i].input);
		free_matrix((void **)&cmd->cmd[i].output);
	}
	if (cmd->n_commands != 0)
		free_matrix((void **)&cmd->cmd);
	cmd->n_commands = 0;
}

void	clean_and_exit_success(t_cmd *cmd)
{
	clean_commands(cmd);
	ft_split_free(cmd->env);
	rl_clear_history();
	exit(EXIT_SUCCESS);
}
