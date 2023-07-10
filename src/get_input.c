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

void	ft_getdatas_red(t_cmd *cmd, char *one_cmd)
{
	int	i;
	int	ic;

	i = 0;
	ic = 0;
	while (one_cmd[i])
	{
		if (one_cmd[i] == '>')
		{
			i++;
			if (one_cmd[i] == '>')
			{
				i++;
				while (one_cmd[i] && one_cmd[i] != ' ' && one_cmd[i] != '>'
					&& one_cmd[i] != '<')
				{
					cmd->outfile[ic] = one_cmd[i];
					printf("Copiando: %c\n", cmd->outfile);
					ic++;
					i++;
				}
				printf("OUTFILE = %s\n", cmd->outfile);
			}
			/* else
			{

			} */
		}
		i++;
	}
}

void	ft_getdatas_nored(t_cmd *cmd, char *one_cmd)
{
	int		i;
	char	**split_sp;

	i = 0;
	split_sp = ft_split_shell(one_cmd, ' ');
	cmd->cmd = split_sp[0];
	cmd->infile_redirect = 0;
	cmd->outfile_redirect = 1;
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
		printf("CMD despues = %s\n", cmd[i].cmd);
		i++;
	}
	free_matrix(split_pi);
}
