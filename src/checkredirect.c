/* #include "../include/minishell.h"

static int ft_sintaxred(char *str)
{
	int	i;

	i = 0;

}

int	ft_checksintaxred(char *input)
{
	int	i;
	char **split_pi;

	i = 0;
	if (ft_strchr(input, '<') || ft_strchr(input, '<'))
	split_pi = ft_split_shell(input, '|');
	while (split_pi[i])
	{
		if (ft_sintaxred(split[i]) == 1)
		{
			err_msg("parse error near `>>'");
			return (1);
		}
		i++;
	}
	free_matrix(split_pi);
	return (0);
} */
