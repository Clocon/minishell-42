#include "../include/minishell.h"

void	ft_scapespaces(char *str, int *i)
{
	while (str[*i] && str[*i] == ' ')
		*i += 1;
}

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

int	ft_checksymbols(char *cmd, int symbol)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == symbol)
		{
			while (cmd[i] == '<' || cmd[i] == '>')
				i++;
			ft_scapespaces(cmd, &i);
			if (cmd[i] && (cmd[i] == '<' || cmd[i] == '>'))
				return (1);
			else
				return (0);
		}
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
			if (ft_strncmp(&cmd[i], "><", 2) == 0 || cmd[i + 1] == 0
				|| ft_strncmp(&cmd[i], ">>>", 3) == 0)
				return (1);
		}
		else if (cmd[i] == '<')
		{
			if (ft_strncmp(&cmd[i], "<<<", 3) == 0 || cmd[i + 1] == 0)
				return (1);
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
	while (split[i] != 0)
	{
		if (ft_existred(split[i])
			&& (ft_sintaxred(split[i]) == 1
				|| ft_checksymbols(split[i], '>') == 1
				|| ft_checksymbols(split[i], '<') == 1))
		{
			err_msg_sintax("Syntax error near unexpected token `>'\n");
			return (1);
		}
		i++;
	}
	free_matrix(split);
	return (0);
}
