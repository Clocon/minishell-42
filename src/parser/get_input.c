#include "../../include/minishell.h"

/**
 * @brief Cuando se detecta heredoc en el input del usuario, se queda esperando
 * la entrada de datos del usuario hasta que introduzca la palabra clave. 
 * Guarda el input del usuario en un fichero temporal en la carpeta temporal del 
 * sistema para posteriormente utilizarlo como infile en el comando introducido
 * 
 * @param cmd 
 */
void	ft_heredoc(t_cmd *cmd)
{
	int		tmp_fd;
	char	*input;

	tmp_fd = open(HEREDOC_FILE, O_TRUNC | O_CREAT | O_RDWR, 0644);
	input = readline("> ");
	while (input && ft_strncmp(input, cmd->infile, ft_strlen(cmd->infile) + 1))
	{
		write(tmp_fd, input, ft_strlen(input));
		write(tmp_fd, "\n", 1);
		input = readline("> ");
	}
	close(tmp_fd);
	free(cmd->infile);
	cmd->infile = HEREDOC_FILE;
}

static char	*ft_getname(char *cmd, int *j)
{
	int		i;
	int		start;
	char	*name;
	char	*aux;

	i = 0;
	name = 0;
	while (cmd[i] && cmd[i] != ' ' && cmd[i] != '<' && cmd[i] != '>')
	{
		start = i;
		if (ft_foundquotes(cmd, &i))
			aux = ft_substr(cmd, start + 1, (i - start) - 1);
		else
			aux = ft_substr(cmd, start, 1);
		name = ft_strjoin_free(name, aux);
		free(aux);
		i++;
	}
	*j += i;
	return (name);
}

void	ft_getdatas(t_cmd *cmd, char *one_cmd, t_pipe *pipex)
{
	int			i;
	t_typetoken	type;

	i = 0;
	type = WORD;
	while (one_cmd[i])
	{
		if (one_cmd[i] == '>')
		{
			cmd->outfile_redirect = 1;
			if (type == RED_OUT)
			{
				cmd->outfile_redirect = 2;
				type = RED_APPEND;
			}
			else
				type = RED_OUT;
		}
		else if (one_cmd[i] == '<')
		{
			cmd->infile_redirect = 1;
			if (type == RED_IN)
				type = RED_HERE;
			else
				type = RED_IN;
		}
		else if (one_cmd[i] != ' ' && one_cmd[i] != '\t')
		{
			if (type == RED_IN || type == RED_HERE)
			{
				if (cmd->infile && type == RED_IN)
					free(cmd->infile);
				cmd->infile = ft_getname(&one_cmd[i], &i);
				if (type == RED_HERE)
					ft_heredoc(cmd);
			}
			else if (type == RED_OUT || type == RED_APPEND)
			{
				if (!cmd->outfile)
					cmd->outfile = ft_getname(&one_cmd[i], &i);
				else
				{
					close(open(cmd->outfile, O_CREAT | O_RDWR | O_TRUNC, 0644));
					free(cmd->outfile);
					cmd->outfile = ft_getname(&one_cmd[i], &i);
				}
			}
			else if (!cmd->cmd)
			{
				cmd->cmd = ft_getname(&one_cmd[i], &i);
				cmd->args = ft_addarray(cmd->cmd, cmd->args);
				cmd->cmd = ft_getcmd(*pipex, cmd->cmd);
			}
			else
				cmd->args = ft_addarray(ft_getname(&one_cmd[i], &i), cmd->args);
			type = WORD;
		}
		if (one_cmd[i])
			i++;
	}
}

t_cmd	*ft_getinput(char *input, t_pipe *pipex, t_cmd *cmd)
{
	int		i;
	char	**split_pi;

	i = 0;
	split_pi = ft_split_shell(input, '|');
	split_pi = ft_cleanspaces(split_pi);
	cmd = malloc(sizeof(t_cmd) * pipex->n_cmd);
	while (i < pipex->n_cmd)
	{
		cmd[i].infile_redirect = 0;
		cmd[i].outfile_redirect = 0;
		cmd[i].infile = NULL;
		cmd[i].outfile = NULL;
		cmd[i].args = NULL;
		cmd[i].cmd = NULL;
		ft_getdatas(&cmd[i], split_pi[i], pipex);
		i++;
	}
	free_matrix(split_pi);
	return (cmd);
}





/*     	i = 0;
 	printf("ncmd = %D\n", pipex->n_cmd);
	 while (i < pipex->n_cmd)
	{
		printf("\n\n---* CMD = %s *---\n", (cmd[i]).cmd);
		i_s = 0;
		while ((cmd[i]).args && (cmd[i]).args[i_s])
		{
			printf("---* Args_%s = %s *---\n", (cmd[i]).cmd, (cmd[i]).args[i_s]);
			i_s++;
		}
		printf(">Infile_name = %s\n", (cmd[i]).infile);
		printf("<Outfile_name = %s\n", (cmd[i]).outfile);
		i++;
	}*/