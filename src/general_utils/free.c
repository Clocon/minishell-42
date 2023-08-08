#include "../../include/minishell.h"

/**
 * @brief Libera la memoria asignada a un char ** por completo
 * 
 * @param str char ** a liberar
 */
void	free_matrix(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}
/**
 * @brief Cierra las tuberias de un pipe abierto
 * 
 * @param tube 
 */
void	close_pipes(int *tube)
{
	close(tube[0]);
	close(tube[1]);
}
/**
 * @brief No hace nada :( solo exit
 * 
 * @param pipe 
 */
void	clean_success(t_pipe *pipe)
{
	(void)pipe;
	//free_matrix(pipe->envp);
	exit(0);
}
