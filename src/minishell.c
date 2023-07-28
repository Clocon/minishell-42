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

void	ft_getline(t_pipe *pipex/*,  t_cmd *cmd */)
{
	char	*input;
	char	*text_minishell;

	while (1)
	{
		text_minishell = ft_get_text_minishell();
		input = readline(text_minishell);
		if (!ft_strncmp(input, "exit", 5) || !ft_strncmp(input, "EXIT", 5))
		{
			free(input);
			free(text_minishell);
			break ;
		}
		add_history(input);
		if (ft_strlen(input) > 0 && ft_strlen(ft_strtrim(input, " ")) > 0)
			ft_checkpipe(input, pipex);
		free(input);
		free(text_minishell);
	}
}

/* void	leaks(void)
{
	system("leaks -q minishell");
} */

int	main(int argc, char **argv, char **envp)
{
//	atexit(leaks);
	t_pipe	pipex;
//	t_cmd	*cmd;

//	(void)argc;
	(void)argv;

//	cmd = malloc(sizeof(t_cmd) * 3);
	pipex.fd_in = dup(0);
	//pipex.tmp_in = dup(0);
	pipex.tmp_out = dup(1);
	pipex.envp = envp;
/* 	cmd[0].args = ft_split("fdgchjil -l -a", ' ');
	cmd[0].cmd = "fdgchjil";
	pipex.envp = envp;
	cmd[1].args = ft_split("wc -l", ' ');
	cmd[1].cmd = "/usr/bin/wc";
	cmd[2].args = ft_split("cat -e", ' ');
	cmd[2].cmd = "/bin/cat"; */

	if (argc != 1)
		argc_error();
	printf("%s", (char *)&(HEADER));
	ft_getline(&pipex);
	exit(0);
}
