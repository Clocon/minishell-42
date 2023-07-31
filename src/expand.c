#include "../include/minishell.h"

static int	ft_ignorequotes(char *str, int *i)
{
	char	com;

	com = 0;
	if (str[*i] == '\'' && str[*i] != 0)
	{
		com = str[*i];
		*i = *i + 1;
		while (str[*i] != 0 && str[*i] != com)
			*i = *i + 1;
		return (1);
	}
	return (0);
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
	if (var[0] && var[0] == '?')
	{
		aux = ft_itoa(pipex->shell_exit);
		i++;
		while (var[i] && var[i] != '$')
			i++;
		return (ft_strjoin_free(aux, ft_substr(var, 1, i - 1)));
	}
	while (var[size] != ' ' && var[size] != '\t' && var[size] != '\''
		&& var[size] != '"' && var[size] != '$' && var[size])
		size++;	
	if (var[size - 1] == '"')
	{
		var[size - 1] = '\0'; size--;
	}
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

/* char	*ft_expandit(char *input, t_pipe *pipex)
{
	int		i;
	int		start;
	char	*result;
	char	*aux;

	i = 0;
	start = 0;
	result = 0;
	while (input[i])
	{
		if (ft_ignorequotes(input, &i) == 1)
		{
			aux = ft_substr(input, start, i);
			aux = ft_strtrim(aux, "'");
			result = ft_strjoin_free(result, aux);
			start = i;
			i++;
			free(aux);
		}
		else if (ft_foundquotes(input, &i))
		{
			aux = ft_substr(input, start, i);
			aux = ft_strtrim(aux, "\"");
			aux = ft_getenv(aux, pipex);
			result = ft_strjoin_free(result, aux);
		}
		else if (input[i] == '$')
		{
			i++;
			aux = ft_getenv(&input[i], pipex);
			result = ft_strjoin_free(result, aux);
			while (input[i] != ' ' && input[i] != '\t' && input[i] && input[i] != '$')
			{
				printf("SOY CONCHA");
				i++;
			}
			free(aux);
		}
		else if (input[i])
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
} */

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

//hol'a '$USER mundo

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
		if (ft_ignorequotes(input, &i) == 1)
			aux = ft_substr(input, start + 1, (i - start) - 1);
		else if (input[i] == '$')
		{
			i++;
			aux = ft_getenv(&input[i], pipex);
			while (input[i] && input[i] != ' ' && input[i] != '\t'
				&& input[i] != '$' && input[i] != '\'' && input[i] != '"')
			{
				i++;
				if (input[i] == '$' || input[i] == '\''
					|| input[i] == '"' || input[i] == ' ')
				{
					i--;
					break ;
				}
			}
		}
		else if (input[i] == '"')
			aux = 0;
		else
			aux = ft_substr(input, start, 1);
		result = ft_strjoin_free(result, aux);
		i++;
		start = i;
		free(aux);
	}
	return (result);
}

prueba pendiente: no funtsiona echo "'Hola" "esto" "eso"