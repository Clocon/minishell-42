#include "../../include/minishell.h"

void	argc_error(void)
{
	printf("Structure: ./minishell\n");
	exit(1);
}

void	err_msg(char *str)
{
	ft_putstr_fd("\033[31;1m* \033[0mMiniShell: ", 2);
	//perror (str);
	ft_putstr_fd(str, 2);
}

void	err_msg_exit(char *str)
{
	ft_putstr_fd("\033[31;1m* \033[0mMiniShell: ", 2);
	ft_putstr_fd(str, 2);
	//perror (str);
	exit(1);
}

void	err_msg_sintax(char *str)
{
	ft_putstr_fd("\033[31;1m* \033[0mMiniShell: ", 2);
	ft_putstr_fd(str, 2);
}
