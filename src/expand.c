#include "../include/minishell.h"

char	*ft_getenv(char *var, t_pipe *pipex)
{
	int		i;
	char	*aux;
	int		size;

	i = 0;
	size = 0;
	while (var[size] != ' ' && var[size] != '\t'
		&& var[size] != '$' && var[size])
		size++;
	printf("VAR = %s\n\n", var);
	while (pipex->envp[i])
	{
		aux = ft_strchr(pipex->envp[i], '=') + 1;
		if (size == aux - pipex->envp[i] - 1)
			if (ft_strncmp(var, pipex->envp[i], size) == 0)
				return (ft_strdup(aux));
		i++;
	}
	return (ft_strdup(""));
}

char	*ft_expandit(char *input, t_pipe *pipex)
{
	int		i;
	int		start;
	char	*result;
	char	*aux;

	i = 0;
	start = 0;
	result = 0;
	(void)pipex;
	while (input[i])
	{
		if (ft_foundquotes(input, &i))
		{
			aux = ft_substr(input, start, i);
			result = ft_strjoin_free(result, aux);
			start = i;
			i++;
			free(aux);
		}
		else if (input[i] == '$')
		{
			i++;
			aux = ft_getenv(&input[i], pipex);
			result = ft_strjoin_free(result, aux);
			while (input[i] != ' ' && input[i] != '\t' && input[i])
				i++;
			free(aux);
		}
		if (input[i])
		{
			aux = ft_substr(input, start, 1);
			result = ft_strjoin_free(result, aux);
			start = i + 1;
			i++;
			free(aux);
		}
		printf("AUX = %s..\n", aux);
	}
	printf("RESULT = %s.\n", result);
	return (result);
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
