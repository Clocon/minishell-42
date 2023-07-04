#include "../include/minishell.h"

static void	ft_getpath(t_pipe *pipex)
{
	int		i;

	i = 0;
	while (ft_strnstr(pipex->envp[i], "PATH=", 5) == 0)
		i++;
	if (i == ft_sizearray(pipex->envp))
		pipex->path = 0;
	else
	{
		pipex->path = ft_calloc(ft_strlen(pipex->envp[i] + 5), sizeof(char));
		if (!pipex->path)
			err_msg_sintax("PATH_ERROR");
		pipex->path = ft_split(pipex->envp[i] + 5, ':');
	}
}

/* static char	*ft_getcmd(t_pipe pipex, char *cmd)
{
	int		i;
	char	*aux;
	char	*c;
	char	*ex;

	i = 0;
	while (cmd[i] != 0 && cmd[i] != ' ')
		i++;
	ex = ft_substr(cmd, 0, i);
	i = 0;
	if (access(ex, X_OK) == 0)
		return (ex);
	while (pipex.path[i])
	{
		aux = ft_strjoin(pipex.path[i], "/");
		c = ft_strjoin(aux, ex);
		free (aux);
		if (access(c, X_OK) == 0)
			return (c);
		free (c);
		i++;
	}
	return (cmd);
} */

int	ft_consecutivepipes(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		ft_foundquotes(input, &i);
		if (input [i] == '|' && input[i + 1] != 0 && input[i + 1] == '|')
			return (1);
		i++;
	}
	return (0);
}

int	ft_checksintaxpipex(char *input)
{
	int		i;
	char	**split;

	i = -1;
	split = ft_split_shell(input, '|');
	split = ft_cleanspaces(split);
	if (ft_countpipe(input) > ft_sizearray(split) || input[0] == '|'
		|| ft_consecutivepipes(input) == 1)
	{
		err_msg_sintax("parse error near `|'\n");
		free_matrix(split);
		return (1);
	}
	if (ft_countpipe(input) != ft_sizearray(split) - 1)
	{
		while (split[++i])
		{
			if (ft_strlen(split[i]) == 0)
			{
				err_msg_sintax("parse error near `|'\n");
				free_matrix(split);
				return (1);
			}
		}
	}
	free_matrix(split);
	return (0);
}

char	*ft_checkpipe(char *input, t_pipe *pipex)
{
	char	**split_pi;
	char	*input_aux;

	input = ft_strtrim(input, " ");
	if (ft_checkinput(input, pipex) == 0)
	{
		split_pi = ft_split_shell(input, '|');
		split_pi = ft_cleanspaces(split_pi);
		pipex->n_cmd = ft_sizearray(split_pi);
		while (ft_countpipe(input) + 1 != pipex->n_cmd)
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
		}
		free_matrix(split_pi);
	}
	return (input);
}

int	ft_checkinput(char *input, t_pipe *pipex)
{
	int		i;
	char	**split_pi;
//	t_cmd	*cmd;

	i = 0;
	split_pi = ft_split_shell(input, '|');
	if (ft_checkquotes(input) == 0 && ft_checksintaxpipex(input) == 0 
		&& ft_checkredirect(input) == 0)
	{
		ft_getpath(pipex);
		pipex->n_cmd = ft_sizearray(split_pi);
		//cmd = malloc(sizeof(t_cmd *) * pipex->n_cmd);
		while (split_pi[i])
		{
			//printf("INPUT %d = %s\n", i, split_pi[i]);
			i++;
		}
		free_matrix(split_pi);
		free_matrix(pipex->path);
//		free(cmd);
		return (0);
	}
	else
	{
		free_matrix(split_pi);
		//free_matrix(pipex->path);
		return (1);
	}
}
