#include "../include/minishell.h"

void	sigint_handler(int sig)
{
	(void) sig;
	rl_on_new_line();
	rl_redisplay();
	ft_putstr_fd("  ", 1);
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	ctrl_d(char *input, t_cmd *cmd)
{
	if (!input)
	{
		clean_and_exit_success(cmd);
	}
}
