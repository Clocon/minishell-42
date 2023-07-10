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

void	ft_getdatas(t_cmd *cmd, char *one_cmd)
{
	int		i;
	int		is;
	char	**split_sp;

	i = 0;
	is = 0;
	split_sp = ft_split_shell(one_cmd, ' ');
	if (ft_existred(one_cmd) == 0)
	{
		cmd->cmd = split_sp[is];
		cmd->args = malloc((sizeof(char *)) * (ft_sizearray(split_sp) + 1));
		while (split_sp[is] != 0)
		{
			cmd->args[is] = split_sp[is];
			printf("ARGS = %s\n", cmd->args[is]);
			is++;
		}
		is = 0;
	}
	free_matrix(split_sp);
}


void	ft_getinput(char *input, t_pipe *pipex)
{
	int		i;
	int		i_s;
	char	**split_pi;
	t_cmd	*cmd;

	i = 0;
	i_s = 0;
	split_pi = ft_split_shell(input, '|');
	split_pi = ft_cleanspaces(split_pi);
	cmd = malloc(sizeof(t_cmd) * pipex->n_cmd);
	while (i < pipex->n_cmd)
	{
		cmd[i].infile_redirect = 0;
		cmd[i].outfile_redirect = 1;
		cmd[i].infile = 0;
		cmd[i].outfile = 0;
		printf("infile = %d // outfile = %d \n", cmd[i].infile_redirect, cmd[i].outfile_redirect);
		ft_getdatas(&cmd[i], split_pi[i]);
		i++;
	}
	free_matrix(split_pi);
}
