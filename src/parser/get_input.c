#include "../../include/minishell.h"

t_typetoken	ft_redirectstatus(char current, t_cmd *cmd, t_typetoken status)
{
	if (current == '>')
	{
		cmd->outfile_redirect = 1;
		if (status == RED_OUT)
		{
			cmd->outfile_redirect = 2;
			status = RED_APPEND;
		}
		else
			status = RED_OUT;
	}
	else if (current == '<')
	{
		cmd->infile_redirect = 1;
		if (status == RED_IN)
			status = RED_HERE;
		else
			status = RED_IN;
	}
	return (status);
}

static void	ft_fillcmd(char *one_cmd, int *i, t_pipe *pipex, t_cmd *cmd)
{
	if (!cmd->cmd)
	{
		cmd->cmd = ft_getname(&one_cmd[*i], i);
		cmd->args = ft_addarray(ft_strdup(cmd->cmd), cmd->args);
		cmd->cmd = ft_getcmd(*pipex, cmd->cmd);
	}
	else
	{
		cmd->args = ft_addarray(ft_getname(&one_cmd[*i], i), cmd->args);
	}
}

static void	ft_fillfile(char *one_cmd, int *i, t_cmd *cmd, t_typetoken redtype)
{
	if (redtype == RED_IN || redtype == RED_HERE)
	{
		if (cmd->infile && redtype == RED_IN)
			free(cmd->infile);
		cmd->infile = ft_getname(&one_cmd[*i], i);
		if (redtype == RED_HERE)
			ft_heredoc(cmd);
	}
	else if (redtype == RED_OUT || redtype == RED_APPEND)
	{
		if (!cmd->outfile)
			cmd->outfile = ft_getname(&one_cmd[*i], i);
		else
		{
			close(open(cmd->outfile, O_CREAT | O_RDWR | O_TRUNC, 0644));
			free(cmd->outfile);
			cmd->outfile = ft_getname(&one_cmd[*i], i);
		}
	}
}

static void	ft_getdatas(t_cmd *cmd, char *one_cmd, t_pipe *pipex)
{
	int			i;
	t_typetoken	status;

	i = 0;
	status = WORD;
	while (one_cmd[i])
	{
		status = ft_redirectstatus(one_cmd[i], cmd, status);
		if (one_cmd[i] != ' ' && one_cmd[i] != '\t' && one_cmd[i] != '<'
			&& one_cmd[i] != '>')
		{
			if (status == WORD)
				ft_fillcmd(one_cmd, &i, pipex, cmd);
			else
				ft_fillfile(one_cmd, &i, cmd, status);
			status = WORD;
		}
		i++;
	}
}

/**
 * @brief Recibe la entrada del usuario a ejecutar en minishell y recoge
 * en un array de cmd (comandos) los datos introducidos en la variable 
 * correspondiente.
 * 
 * 
 * @param input string con la entrada del usuario
 * @param pipex estructura con las variables de entorno 
 * @param cmd puntero a una estructura de comandos vacia
 * @return t_cmd* puntero de comandos 
 */
t_cmd	*ft_getinput(char *input, t_pipe *pipex)
{
	int		i;
	char	**split_pi;
	t_cmd	*cmd;

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