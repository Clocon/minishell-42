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

void	ft_getline(t_pipe *pipex, t_cmd *cmd)
{
	char	*input;
	char	*text_minishell;

	while (1)
	{
		signal(SIGINT, sigint_handler);
		text_minishell = ft_get_text_minishell();
		input = readline(text_minishell);
		ctrl_d(input, pipex);
		add_history(input);
		ft_checkinput(input, pipex);
		if (ft_strncmp(input, "pitos", 5) == 0)
		{
			child_generator(pipex, cmd);
			dup2(1, 1);
		}
		else if (!ft_strncmp(input, "exit", 5) || !ft_strncmp(input, "EXIT", 5))
		{
			free(input);
			break ;
		}
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
	//atexit(leaks);
	t_pipe	pipex;
	t_cmd	*cmd;
/* 	char **str;
	int i = -1;
	str = split_args("ls | coca | cola | locooo \" | si o q \"", '|');
	while (str[++i])
	{
		printf("%s\n", str[i]);
	} */
	(void)argc;
	(void)argv;
	pipex.n_cmd = 3;
	pipex.envp = envp;
	cmd = malloc(sizeof(t_cmd) * pipex.n_cmd);
	pipex.fd_in = dup(0);
	//pipex.tmp_in = dup(0);
	pipex.tmp_out = dup(1);
	cmd[0].args = ft_split("ECHO -n 'SALUDOosS' ", ' ');
	cmd[0].cmd = "echo";
	cmd[0].in_redir = 0;
	//cmd[0].infile = "ina.txt";
	cmd[0].out_redir = 0;
/* 	cmd[1].args = ft_split("wc -l", ' ');
	cmd[1].cmd = "/usr/bin/wc";
	cmd[1].in_redir = 0;
	cmd[1].out_redir = 0; */
	cmd[1].args = ft_split("cat -e", ' ');
	cmd[1].cmd = "/bin/cat";
	cmd[1].in_redir = 0;
	cmd[1].out_redir = 1;
	cmd[1].outfile = "sexy.txt";

	if (argc != 1)
		argc_error();
	printf("%s", (char *)&(HEADER));
	ft_getline(&pipex, cmd);
	exit(0);
}
