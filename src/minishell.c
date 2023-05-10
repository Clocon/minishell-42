#include "../include/minishell.h"

/* static char	*find_path(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
} */

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


void	ft_getline(t_pipe *pipex, char **envp)
{
	char	*input;
	char	*text_minishell;
	int		to_wait;

	while (1)
	{
		text_minishell = ft_get_text_minishell();
		input = readline(text_minishell);
		free(text_minishell);
		add_history(input);
		if (ft_strncmp(input, "pitos", 5) == 0)
		{
			child_generator(pipex, 3, envp);
			wait(&to_wait);
		}
		if (!ft_strncmp(input, "exit", 5) || !ft_strncmp(input, "EXIT", 5))
		{
			free(input);
			break ;
		}
		free(input);
	}
}

int	main(int argc, char **argv, char **envp)
{
	int		**tube;
	t_pipe	*pipex;

	(void)argc;
	(void)argv;
	pipex = malloc(sizeof(t_pipe) * 3);
	tube = pipes_generator(3);
	printf("%d, %d \n",tube[0][0],tube[0][1] );

	pipex[0].args = ft_split("ls -l -a", ' ');
	pipex[0].cmd = "/bin/ls";
	pipex[0].fd_in = open("in.txt", O_RDONLY);
	pipex[0].fd_out = tube[0][1];
	pipex[1].args = ft_split("cat -e", ' ');
	pipex[1].cmd = "/bin/cat";
	pipex[1].fd_in = tube[0][0];
	pipex[1].fd_out = tube[1][1];
	pipex[2].args = ft_split("wc -l", ' ');
	pipex[2].cmd = "/usr/bin/wc";
	pipex[2].fd_in = tube[1][0];
	pipex[2].fd_out = open("out.txt", O_TRUNC | O_CREAT | O_RDWR, 0644);

	//child_generator(pipex, 3);

	printf("%s", (char *)&(HEADER));
	ft_getline(pipex, envp);
}
