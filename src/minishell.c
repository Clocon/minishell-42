#include "../include/minishell.h"

void	ft_getline(t_pipe *pipex)
{
	char	*input;
	char	*aux;

	while (1)
	{
		ft_getpath(pipex);
		input = readline("\033[32;1m* \033[0mMiniShell $> ");
		if (!input)
			exit(0);
		add_history(input);
		aux = ft_strtrim(input, " ");
		if (ft_strlen(input) > 0 && ft_strlen(aux) > 0)
			ft_checkpipe(input, pipex);
		free(aux);
		free(input);
		free_matrix(pipex->path);
	}
}

void	leaks(void)
{
	system("leaks -q minishell");
}
int	main(int argc, char **argv, char **envp)
{
	atexit(leaks);
	t_pipe	pipex;

	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	(void)argv;
	pipex.fd_in = dup(0);
	pipex.tmp_out = dup(1);
	pipex.envp = ft_arraydup(envp);
	if (argc != 1)
		argc_error();
	printf("%s", (char *)&(HEADER));
	ft_getline(&pipex);
	exit(0);
}

//	atexit(leaks);