#include "../include/minishell.h"

int	ft_sizearray(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return (0);
	while (array[i])
		i++;
	return (i);
}

char	**ft_cleanspaces(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		split[i] = ft_strtrim(split[i], " ");
		i++;
	}
	return (split);
}

char	*ft_checkpipe(char *input, t_pipe *pipex)
{
	int		n_pipe;
	char	**split_pi;
	char	*input_aux;

	if (ft_checkinput(input, pipex) == 0)
	{
		split_pi = ft_split_shell(input, '|');
		split_pi = ft_cleanspaces(split_pi);
		pipex->n_cmd = ft_sizearray(split_pi);
		n_pipe = ft_countpipe(input);
		while (n_pipe + 1 != pipex->n_cmd)
		{
			input_aux = readline("pipe>");
			input = ft_strjoin_free(input, input_aux);
			free (input_aux);
			free_matrix(split_pi);
			if (ft_checkinput(input, pipex) == 1)
				return (input);
			split_pi = ft_split_shell(input, '|');
			split_pi = ft_cleanspaces(split_pi);
			pipex->n_cmd = ft_sizearray(split_pi);
			n_pipe = ft_countpipe(input);
		}
		free_matrix(split_pi);
	}
	return (input);
}

static int	ft_checkclose(char *quotes)
{
	int	i;
	int	com;

	i = 0;
	while (quotes[i])
	{
		if (quotes[i] == 39 || quotes[i] == '"')
		{
			com = quotes[i];
			ft_foundquotes(quotes, &i);
			if (quotes[i] != com)
				return (0);
		}
		i++;
	}
	return (1);
}

int	ft_checkquotes(char *input)
{
	char	**quotes;
	int		i;
	int		s;
	char	com;

	i = 0;
	s = 0;
	com = 0;
	quotes = ft_split_shell(input, ' ');
	while (quotes[i])
	{
		if (ft_strchr(quotes[i], '\'') || ft_strchr(quotes[i], '"'))
		{
			if (ft_checkclose(quotes[i]) == 0)
			{
				err_msg("Sintax error: ' or \" must be closed\n");
				return (1);
			}
		}
		i++;
	}
	free_matrix(quotes);
	return (0);
}
