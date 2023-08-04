#include "../include/minishell.h"

/**
 * @brief Añade un string a un char ** al final del mismo. Si no existe, 
 * lo crea, si existe lo añade a la última posición.
 * 
 * @param str string a añadir
 * @param array char ** al que añadir 
 * @return char**
 */
char	**ft_addarray(char *str, char **array)
{
	char	**new_array;
	int		i;

	if (!array)
	{
		array = ft_calloc(sizeof(char *), 2);
		array[0] = str;
		return (array);
	}
	else
	{
		new_array = ft_calloc(sizeof(char *), ft_sizearray(array) + 2);
		i = -1;
		while (array[++i])
			new_array[i] = ft_strdup(array[i]);
		new_array[i] = str;
		return (new_array);
	}
}

/**
 * @brief Elimina un elemento de un char **
 * 
 * @param pos int con la posición a eliminar
 * @param array char ** del que eliminar un elemento
 * @return char** sin ese elemento
 */
char	**ft_deleteitem(int pos, char **array)
{
	int		i;
	char	**new_array;

	i = 0;
	if (!array || pos < 0 || pos > ft_sizearray(array))
		return (array);
	new_array = ft_calloc(sizeof(char *), ft_sizearray(array));
	while (array[i])
	{
		if (i >= pos)
			new_array[i] = array[i + 1];
		else
			new_array[i] = array[i];
		i++;
	}
	return (new_array);
}

/**
 * @brief Localiza la posición de una variable de entorno 
 * 
 * @param var string con el nombre de la variable
 * @param envp char ** con todas las variables
 * @return int posición donde se localiza, si no la localiza devuelve -1
 */
int	ft_foundenv(char *var, char **envp)
{
	int		i;
	char	*aux;

	i = 0;
	if (!var[0])
		return (-1);
	while (envp[i])
	{
		aux = ft_strchr(envp[i], '=') + 1;
		if (ft_strlen(var) == aux - envp[i] - 1)
			if (ft_strncmp(var, envp[i], ft_strlen(var)) == 0)
				return (i);
		i++;
	}
	return (-1);
}
