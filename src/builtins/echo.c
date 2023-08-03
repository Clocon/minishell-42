#include "../../include/minishell.h"

void	ft_echo(t_cmd *cmd)
{
	int	len;
	int	i;
	int	j;

	j = 1;
	if (cmd->args[j][0] && cmd->args[j][0] == '"')
		cmd->args[j] = ft_strtrim(cmd->args[1], "\"");
	else if (cmd->args[j][0] && cmd->args[j][0] == '\'')
		cmd->args[j] = ft_strtrim(cmd->args[1], "'");
	while (cmd->args[++j])
	{
		cmd->args[j] = check_trim(cmd->args[j]);
		len = ft_strlen(cmd->args[j]);
		i = -1;
		while (++i < len)
		{
			if (!cmd->args[j][i + 1])
				if (cmd->args[j][len - 1] == '\n' && i == len -1)
					break ;
			ft_putchar_fd(cmd->args[j][i], 1);
		}
	}
	ft_putstr_fd("%\n", 1);
}
