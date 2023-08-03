#include "../include/minishell.h"

/**
 * @brief Función para medir un char **
 * 
 * @param array char **
 * @return int con el tamaño
 */
int	ft_sizearray(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return (0);
	while (array[i])
		i++;
	return (i);
}


/**
 * @brief función para contar el número de '|' (pipes) en un string, 
 * sin tener en cuenta los que están entre comillas (dobles o simples)
 * 
 * @param input char *
 * @return int con el número de | localizados
 */
int	ft_countpipe(char *input)
{
	int	i;
	int	npipe;

	i = 0;
	npipe = 0;
	while (input[i])
	{
		ft_foundquotes(input, &i);
		if (input[i] == '|')
			npipe++;
		i++;
	}
	return (npipe);
}

/**
 * @brief Función que elimina ' ' (espacios) (si los hubiera), 
 * al comienzo y al final del string, recibe un char ** ,va liberando
 * cada item y lo sustituye por el nuevo string sin espacios.
 * 
 * @param split char **
 * @return char** 
 */
char	**ft_cleanspaces(char **split)
{
	int		i;
	char	*trim;

	i = 0;
	while (split[i])
	{
		trim = ft_strtrim(split[i], " ");
		free(split[i]);
		split[i] = trim;
		i++;
	}
	return (split);
}

/**
 * @brief Verifica si tanto comillas simples como comillas
dobles están cerradas en un string, sin tener en cuenta las comillas que puedan 
estar entre comilladas ya que estas sí pueden estar abiertas.
 * 
 * @param quotes string
 * @return Devuelve 0 si no están cerradas y 1 si lo están.
 */
static int	ft_checkclose(char *quotes)
{
	int	i;
	int	com;

	i = 0;
	while (quotes[i])
	{
		if (quotes[i] == 39 || quotes[i] == '"')
		{
			com = quotes[i];
			ft_foundquotes(quotes, &i);
			if (quotes[i] != com)
				return (0);
		}
		i++;
	}
	return (1);
}

/**
 * @brief Verifica si tanto comillas simples como comillas dobles están cerradas 
 * en un string, sin tener en cuenta las comillas que puedan estar entre comilladas
 * ya que estas sí pueden estar abiertas.
 * 
 * @param input char *
 * @return int 
 */
int	ft_checkquotes(char *input)
{
	char	**quotes;
	int		i;
	int		s;
	char	com;

	i = 0;
	s = 0;
	com = 0;
	quotes = ft_split_shell(input, ' ');
	while (quotes[i])
	{
		if (ft_strchr(quotes[i], '\'') || ft_strchr(quotes[i], '"'))
		{
			if (ft_checkclose(quotes[i]) == 0)
			{
				err_msg_sintax("Syntax error: ' or \" must be closed\n");
				free_matrix(quotes);
				return (1);
			}
		}
		i++;
	}
	free_matrix(quotes);
	return (0);
}
