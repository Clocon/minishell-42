#include "../include/minishell.h"

int	ft_existred(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		ft_foundquotes(input, &i);
		if (input[i] == '>')
			return (1);
		else if (input[i] == '<')
			return (2);
		i++;
	}
	return (0);
}

int	ft_sintaxred(char *cmd)
{
	int	i;

	i = -1;
	while (cmd[++i])
	{
		ft_foundquotes(cmd, &i);
		if (cmd[i] == '>')
		{
			if (ft_strncmp(&cmd[i], "><", 2) == 0
				|| ft_strncmp(&cmd[i], ">>>", 3) == 0)
			{
				err_msg_sintax("parse error near `>'\n");
				return (1);
			}
		}
		else if (cmd[i] == '<')
		{
			if (ft_strncmp(&cmd[i], "<<<", 3) == 0)
			{
				err_msg_sintax("parse error near `<'\n");
				return (1);
			}
		}
	}
	return (0);
}

int	ft_checkredirect(char *input)
{
	char	**split;
	int		i;

	i = 0;
	split = ft_split_shell(input, '|');
	split = ft_cleanspaces(split);
	if (ft_existred(input) != 0)
	{
		while (split[i] && ft_existred(split[i]))
		{
			if (ft_sintaxred(split[i]) == 1)
				return (1);
			i++;
		}
		ft_putstr_fd("encontrado red\n", 1);
	}
	free_matrix(split);
	return (0);
}
