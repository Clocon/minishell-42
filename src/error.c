#include "../include/minishell.h"

void	argc_error(char *str)
{
	printf("%s", str);
	printf("Structure= ./pipex <input.txt> <*numbers_of_cmd> <output.txt>\n");
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
