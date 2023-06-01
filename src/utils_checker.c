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

char	*ft_checkpipe(char *input, t_pipe *pipex)
{
	int		n_pipe;
	char	**split_pi;
	char	*input_aux;

	split_pi = ft_split_shell(input, '|');
	pipex->n_cmd = ft_sizearray(split_pi);
	n_pipe = ft_countpipe(input);
	while (n_pipe + 1 != pipex->n_cmd)
	{
		input_aux = readline("pipe>");
		input = ft_strjoin_free(input, input_aux);
		free (input_aux);
	}
	return (input);
}
