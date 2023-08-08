#include "../../include/minishell.h"

/**
 * @brief Built-in pwd: muestra por pantalla la ruta actual
 * del usuario
 * 
 */
void	ft_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	ft_putstr_fd(pwd, 1);
	ft_putstr_fd("\n", 1);
	free(pwd);
}
