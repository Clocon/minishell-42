#include "../include/minishell.h"

char	*ft_get_text_minishell(void)
{
	char	*text_minishell;
	char	path[1024];
	char	*aux;

	if (getcwd(path, sizeof(path)) == NULL)
		exit(EXIT_FAILURE); //Poner ft_error y liberar lo que haga falta
	aux = ft_strrchr(path, '/') + 1;
	aux = ft_strjoin("\033[36;1m", aux); //Proteger
	text_minishell = ft_strjoin(aux, " -> \033[0m"); //Proteger
	free(aux);
	return (text_minishell);
}

void	ft_getline(t_pipe *pipex)
{
	char	*input;
//	char	*text_minishell;

	while (1)
	{
		//text_minishell = ft_get_text_minishell();
		input = readline("\033[32;1m* \033[0mMiniShell $> ");
		if (!ft_strncmp(input, "exit", 5))
		{
			free(input);
			//free(text_minishell);
			//free_matrix(pipex->path);
			break ;
		}
		add_history(input);
		if (ft_strlen(input) > 0 && ft_strlen(ft_strtrim(input, " ")) > 0)
			ft_checkpipe(input, pipex);
		free(input);
		//free(text_minishell);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_pipe	pipex;

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

/* void	leaks(void)
{
	system("leaks -q minishell");
} 
//	atexit(leaks);*/