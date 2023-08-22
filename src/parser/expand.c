#include "../../include/minishell.h"

static int	ft_ignorequotes(char *str, int *i, int quote)
{
	if (str[*i] == quote && str[*i] != 0)
	{
		*i = *i + 1;
		while (str[*i] != 0 && str[*i] != quote)
			*i = *i + 1;
		return (1);
	}
	return (0);
}

char	*ft_get_exit_status(char *var, t_pipe *pipex)
{
	char	*status;
	int		i;

	status = ft_itoa(pipex->shell_exit);
	i = 1;
	while (var[i] && var[i] != '$')
		i++;
	return (ft_strjoin_free(status, ft_substr(var, 1, i - 1)));
}

char	*ft_getenv(char *var, t_pipe *pipex)
{
	int		i;
	char	*aux;
	int		size;

	i = 0;
	size = 0;
	if (!var[0])
		return (ft_strdup("$"));
	if (var[0] == '$')
		return (ft_itoa(getpid()));
	if (var[0] && var[0] == '?')
		return (ft_get_exit_status(var, pipex));
	while (var[size] != ' ' && var[size] != '\t' && var[size] != '\''
		&& var[size] != '"' && var[size] != '$' && var[size]
		&& var[size] != '|' && var[size] != '\'')
			size++;
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

char	*ft_expand_value(int *i, char *input, t_pipe *pipex)
{
	char	*aux;

	(*i)++;
	aux = ft_getenv(&input[*i], pipex);
	while (input[*i] && input[*i] != ' ' && input[*i] != '\t'
		&& input[*i] != '$' && input[*i] != '\'' && input[*i] != '"')
	{
		(*i)++;
		if (input[*i] == '$' || input[*i] == '\''
			|| input[*i] == '"' || input[*i] == ' ')
		{
			(*i)--;
			break ;
		}
	}
	return (aux);
}

char	*ft_expandit(char *input, t_pipe *pipex, int expand)
{
	int		i;
	int		start;
	char	*result;
	char	*aux;

	i = -1;
	result = 0;
	while (input && input[++i])
	{
		start = i;
		if (expand == 0 && ft_ignorequotes(input, &i, '\'') == 1)
			aux = ft_substr(input, start, (i - start) + 1);
		else if (expand == 0 && ft_ignorequotes(input, &i, '"') == 1)
			aux = ft_expandit(ft_substr(input, start, (i - start) + 1),
					pipex, 1);
		else if (input[i] == '$')
			aux = ft_expand_value(&i, input, pipex);
		else
			aux = ft_substr(input, start, 1);
		result = ft_strjoin_free(result, aux);
		free(aux);
	}
	free(input);
	return (result);
}
