#include "../include/minishell.h"

void	sub_dup2(int zero, int one)
{
	printf("Empiezo sub_Dup!\n");
	dup2(zero, 0);
	dup2(one, 1);
	printf("termino\n");
}

void	check_awk(t_cmd *cmd)
{
	if (ft_strncmp(cmd->args[0], "awk", 3) == 0)
	{	
		if (cmd->args[1][0] == '\'')
			cmd->args[1] = ft_strtrim(cmd->args[1], "'");
		else if (cmd->args[1][0] == '"')
			cmd->args[1] = ft_strtrim(cmd->args[1], "\"");
	}
}
