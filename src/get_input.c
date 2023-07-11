#include "../include/minishell.h"

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

char	*ft_getname(char *cmd, int *j)
{
	int		i;
	char	*file;

	i = 0;
	while (cmd[i] && cmd[i] != ' ' && cmd[i] != '<' && cmd[i] != '>')
	{
		ft_foundquotes(&cmd[i], &i);
		i++;
	}
	i--;
	file = ft_substr(cmd, 0, i + 1);
	file[i + 1] = 0;
	*j += i;
	return (file);
}

void	ft_getfiles(t_cmd *cmd, char *str, int *i, int red)
{
	if (str[*i] == red)
	{
		*i += 1;
		if (red == '>')
			cmd->outfile_redirect = 1;
		else if (red == '<')
			cmd->infile_redirect = 1;
		while (str[*i] == '>' || str[*i] == ' ')
		{
			if (str[*i] == '>')
				cmd->outfile_redirect = 2;
			else if (str[*i] == '<')
				cmd->infile_redirect = 2;
			*i += 1;
		}
		if (red == '>')
			cmd->outfile = ft_getname(&str[*i], i);
		else if (red == '<')
			cmd->infile = ft_getname(&str[*i], i);
	}
}

void	ft_getdatas_red(t_cmd *cmd, char *one_cmd)
{
	int	i;
	int	ic;

	i = 0;
	ic = 0;
	while (one_cmd[i] && i < ft_strlen(one_cmd))
	{
		ft_foundquotes(one_cmd, &i);
		/* if (one_cmd[i] == '>')
		{
			i++;
			cmd->outfile_redirect = 1;
			while (one_cmd[i] == '>' || one_cmd[i] == ' ')
			{
				if (one_cmd[i] == '>')
					cmd->outfile_redirect = 2;
				i++;
			}
			cmd->outfile = ft_getname(&one_cmd[i], &i);
		}
		else if (one_cmd[i] == '<')
		{
			i++;
			cmd->infile_redirect = 1;
			while (one_cmd[i] == '<' || one_cmd[i] == ' ')
			{
				if (one_cmd[i] == '<')
					cmd->infile_redirect = 2;
				i++;
			}
			cmd->infile = ft_getname(&one_cmd[i], &i);
		} */
		if (one_cmd[i] != '<' && one_cmd[i] != '>' && i == 0 && one_cmd[i])
		{
			cmd->cmd = ft_getname(&one_cmd[i], &i);
		}
		else if ((one_cmd[i] == '<' || one_cmd[i] == '>') && one_cmd[i])
			ft_getfiles(cmd, one_cmd, &i, one_cmd[i]);
		i++;
	}
	cmd->args = malloc(sizeof(char *) * 1);
	cmd->args[0] = 0;
}

void	ft_getdatas_nored(t_cmd *cmd, char *one_cmd)
{
	int		i;
	char	**split_sp;

	i = 0;
	split_sp = ft_split_shell(one_cmd, ' ');
	cmd->cmd = split_sp[0];
	cmd->infile_redirect = 0;
	cmd->outfile_redirect = 0;
	cmd->infile = 0;
	cmd->outfile = 0;
	cmd->args = malloc((sizeof(char *)) * (ft_sizearray(split_sp) + 1));
	while (split_sp[i] != 0)
	{
		cmd->args[i] = split_sp[i];
		i++;
	}
	cmd->args[i] = 0;
	free(split_sp);
}

void	ft_getinput(char *input, t_pipe *pipex)
{
	int		i;
	int		i_s;
	char	**split_pi;
	t_cmd	*cmd;

	i = 0;
	i_s = 0;
	printf("input = %s\n", input);
	split_pi = ft_split_shell(input, '|');
	split_pi = ft_cleanspaces(split_pi);
	cmd = malloc(sizeof(t_cmd) * pipex->n_cmd);
	while (i < pipex->n_cmd)
	{
		if (ft_existred(split_pi[i]) == 0)
			ft_getdatas_nored(&cmd[i], split_pi[i]);
		else
			ft_getdatas_red(&cmd[i], split_pi[i]);
		printf("infile = %d // outfile = %d \n", cmd[i].infile_redirect, cmd[i].outfile_redirect);
		printf("OUTFILE name = %s\n", cmd[i].outfile);
		printf("INFILE name = %s\n", cmd[i].infile);
		printf("CMD = %s\n", cmd[i].cmd);
		int a = 0;
		while (cmd[i].args[a])
		{
			printf("ARGS_%d: %s\n",i, cmd[i].args[a]);
			a++;
		}
		i++;
	}
	free_matrix(split_pi);
}
