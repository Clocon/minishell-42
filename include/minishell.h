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
	//char	**path;
	char	**envp;
	char	**args;
	char	*cmd;
	//int		cmd_counter; Mejor pasar int aparte

}	t_cmd;

/* typedef struct s_cmd
{
	char	**infile;
	char	**outfile;
	int		fd_in;
	int		fd_out;
	int		cmd_counter;

}	t_cmd;
 */
typedef struct s_pipe
{
	int		fd_in;
	int		tmp_in;
	int		fd_out;
	int		tmp_out;
}	t_pipe;


char	*ft_get_text_minishell(void);
void	ft_getline(t_pipe *pipex, t_cmd *cmd, char **envp);

/*Functions for pipe_utils.c*/
void	sub_dup2(int zero, int one);
void	check_awk(t_cmd *cmd);
void	child_generator(t_pipe *pipex, t_cmd *cmd, int n_cmd, char **envp);

/*Functions for error.c*/
void	argc_error(void);
void	err_msg(char *str);
void	err_msg_exit(char *str);

/*Functions for frre.c*/
void	free_matrix(char **str);
#endif
