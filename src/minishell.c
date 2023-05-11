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


void	ft_getline(t_pipe *pipex, t_cmd *cmd, char **envp)
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
		printf("HOLIII\n");
		if (ft_strncmp(input, "pitos", 5) == 0)
		{
			child_generator(pipex, cmd, 3, envp);
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
	t_pipe	pipex;
	t_cmd	*cmd;

	(void)argc;
	(void)argv;
	cmd = malloc(sizeof(t_cmd) * 3);
	pipex.fd_in = dup(0);
	pipex.tmp_in = dup(0);
	pipex.tmp_out = dup(1);
	cmd[0].args = ft_split("ls -l -a", ' ');
	cmd[0].cmd = "/bin/ls";
	cmd[1].args = ft_split("cat -e", ' ');
	cmd[1].cmd = "/bin/cat";
	cmd[2].args = ft_split("wc -l", ' ');
	cmd[2].cmd = "/usr/bin/wc";
	//child_generator(pipex, 3);

	printf("%s", (char *)&(HEADER));
	ft_getline(&pipex, cmd, envp);
}
