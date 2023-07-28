#include "../include/minishell.h"

char	*ft_expandit(char *input, t_pipe *pipex)
{
	int		i;
	int		start;
	char	*result;
	char	*aux;

	i = 0;
	start = 0;
	(void)pipex;
	while (input[i])
	{
		if (ft_foundquotes(input, &i))
		{
			aux = ft_substr(input, start + 1, i - 1);
			result = ft_strjoin_free(aux, result);
			start = i;
		}
		i++;
	}
	//free (input);
	return (input);
}

/* void	ft_expandvalues(t_cmd *cmd, t_pipe *pipex)
{
	int	i;

	i = 0;
	cmd->cmd = ft_expandit(cmd->cmd, pipex);
	while (cmd->args[i])
	{
		cmd->args[i] = ft_expandit(cmd->args[i], pipex);
		i++;
	}
	cmd->infile = ft_expandit(cmd->infile, pipex);
	cmd->outfile = ft_expandit(cmd->outfile, pipex);
} */
