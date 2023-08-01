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
		err_msg_sintax("Syntax error near unexpected token `|'\n");
		free_matrix(split);
		return (1);
	}
	if (ft_countpipe(input) != ft_sizearray(split) - 1)
	{
		while (split[++i])
		{
			if (ft_strlen(split[i]) == 0)
			{
				err_msg_sintax("Syntax error near unexpected token `|'\n");
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
	t_cmd	*cmd;

	input = ft_strtrim(input, " ");
	cmd = 0;
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
			{
				pipex->shell_exit = 258;
				return (input);
			}
			split_pi = ft_split_shell(input, '|');
			split_pi = ft_cleanspaces(split_pi);
			pipex->n_cmd = ft_sizearray(split_pi);
		}
		free_matrix(split_pi);
		cmd = ft_getinput((ft_expandit(input, pipex, 0)), pipex, cmd);
		//cmd = ft_getinput(input, pipex, cmd);
		child_generator(pipex, cmd);
	}
	else
		pipex->shell_exit = 258;
	return (input);
}

int	ft_checkinput(char *input, t_pipe *pipex)
{
	if (ft_checkquotes(input) == 0 && ft_checksintaxpipex(input) == 0
		&& ft_checkredirect(input) == 0)
	{
		ft_getpath(pipex);
		return (0);
	}
	else
	{
		pipex->shell_exit = 258;
		return (1);
	}
}
