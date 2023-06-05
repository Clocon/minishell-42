#ifndef MINISHELL_H
# define MINISHELL_H

# define HEADER ("\n\033[32;1m\
███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗     \n\
████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║     \n\
██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║     \n\
██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║     \n\
██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗\n\
╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝\n\
\n\
                A simple shell implemented in C                    \n\
                             By                                    \n\
                --- lumorale && jmerchan ---                       \n\
\n\033[0m")

# include "../libft/includes/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <libgen.h>
# include <signal.h>
# include <fcntl.h>

# define CMD_ERROR "Command not found\n"
# define PIPE_ERROR "Pipe error\n"

typedef struct s_cmd
{
	char	**args;
	char	*cmd;
	char	*infile;
	int		in_redir;// 0 = defecto; 1 = <; 2 = <<
	char	*outfile;
	int		out_redir;// 0 = defecto; 1 = > 2 >>

}	t_cmd;

typedef struct s_pipe
{
	char	**envp;
	char	**path;
	int		tube[2];
	int		fd_in;
	int		tmp_in;
	int		fd_out;
	int		tmp_out;
	int		n_cmd;
}	t_pipe;

/*Functions for minishell.c*/
char	*ft_get_text_minishell(void);
void	ft_getline(t_pipe *pipex, t_cmd *cmd);

/*Functions for pipe.c*/
void	child_generator(t_pipe *pipex, t_cmd *cmd);

/*Functions for pipe_utils.c*/
//void	sub_dup2(int zero, int one);
char	*check_trim(char *str);
int		redir_check(t_pipe *pipex, t_cmd *cmd, int i);

/*Functions for error.c*/
void	argc_error(void);
void	err_msg(char *str);
void	err_msg_exit(char *str);

/*Functions for free.c*/
void	free_matrix(char **str);
void	close_pipes(int *tube);
void	clean_success(t_pipe *pipe);

/*Functions for checker.c*/
void	ft_checkinput(char *input, t_pipe *pipex);

/*Functions for split_pipex.c*/
char	**ft_split_shell(char *str, char s);

/*Functions for signals.c*/
void	sigint_handler(int sig);
void	ctrl_d(char *input, t_pipe *pipe);

/*Functions for *.c from builtins*/
int		builting(t_cmd *cmd);
void	ft_echo(t_cmd *cmd);

#endif
