#include "../include/minishell.h"

void	argc_error(void)
{
	printf("Structure: ./minishell\n");
	exit(1);
}

void	err_msg(char *str)
{
	perror (str);
}

void	err_msg_exit(char *str)
{
	perror (str);
	exit(1);
}

void	err_msg_sintax(char *str)
{
	ft_putstr_fd("\033[31;1mminishell -> \033[0m", 2);
	ft_putstr_fd(str, 2);
}
