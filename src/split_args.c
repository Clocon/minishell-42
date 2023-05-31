#include "../include/minishell.h"

/* static int	word_counter(char *str, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			i++;
			while ((str[i] != '\'' || str[i] == '\"') && str[i] != 0)
				i++;
			j++;
		}
		if (str[i] != c)
		{
			while (str[i] != c && str[i])
				i++;
			j++;
		}
		else
			i++;
	}
	return (j);
}

char	*special_condition(char *s, char c, char c2)
{
	int	len;

	len = 0;
	if (*s == c2)
	{
		s++;
		while ((*s != c2) && *s)
		{
			s++;
			len++;
		}
		if (*s)
			s++;
		len++;
		if (*s == c2)
			len++;
	}
	else if (*s != c)
	{
		while (*s && *s != c && *s != 0)
		{
		len++;
		s++;
		}
	}
	return (s);
}

char	**split_args(char *s, char c)
{
	char	**str;
	int		len;
	int		i;
	char	c2;

	str = malloc(sizeof(char *) * (word_counter(s, c) + 1));
	if (!str)
		return (0);
	i = 0;
	len = 0;
	while (*s)
	{
		printf(" ESTO ES UNA COSA = %c\n", *s);
		if ((*s == '\'' || *s == '"'))
		{
			if (*s == '\'' || *s == '"')
				c2 = *s;
			char *aux = s;
			s = special_condition(s, c, c2);
			printf("VALOR DE LEN = %d\n", len);
			printf("ESTO ES UNA OTRA COSA = %c\n", *s - 10);
			str[i++] = ft_substr(aux, 0, aux - s + 1);
			len = 0;
		}
		else if (*s == c)
			{str[i++] = ft_substr(s - len, 0, len);len = 0;}
		else
			{s++; len++;}
	}
	str[i] = 0;
	return (str);
}
 */

static int	word_counter(char *str, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			i++;
			while ((str[i] != '\'' || str[i] == '\"') && str[i] != 0)
				i++;
			j++;
		}
		if (str[i] != c)
		{
			while (str[i] != c && str[i])
				i++;
			j++;
		}
		else
			i++;
	}
	printf("%d\n", j);
	return (j);
}

static int	special_condition(char *s, char c, char c2)
{
	int	len;
	int	i;

	i = 0;
	len = 0;
	if (s[i] == c2)
	{
		while ((s[++i] != c2) && s[i])
		{
			len++;
		}
		len++;
		if (s[i] == c2)
			len++;
	}
	else if (s[i] != c)
	{
		while (s[i] && s[i] != c && s[i] != 0)
		{
		len++;
		}
	}
	printf("SOY LEN = %d\n", len);
	return (len);
}

char	**split_args(char *s, char c)
{
	char	**str;
	int		i;
	int		j;
	int		len;
	char	c2;

	str = malloc(sizeof(char *) * (word_counter(s, c) + 1));
	if (!str)
		return (0);
	len = 0;
	i = 0;
	j = -1;
	while (s[++j])
	{
		if ((s[j] == '\'' || s[j] == '"') || s[j] == c)
		{
			if (s[j] == '\'' || s[j] == '"')
			{
				c2 = s[j];
				j += special_condition(&s[j], c, c2);
			}
			printf("voy a copiar desde '%c' hasta '%c'\n", s[len], s[j]);
			str[i++] = ft_substr(s, len, j);
			len = j;
		}
/* 		else if (s[j] == c)
		{
			str[i++] = ft_substr(&s[len], 0, j - 1);
			len = j + 1;
		} */
	}
	str[i] = 0;
	return (str);
}
/* char	**split_args(char *s, char c)
{
	char	**str;
	int		len;
	int		i;
	char	c2;

	str = malloc(sizeof(char *) * (word_counter(s, c) + 1));
	if (!str)
		return (0);
	i = 0;
	while (*s)
	{
		if ((*s == '\'' || *s == '"') || *s != c)
		{
			if (*s == '\'' || *s == '"')
				c2 = *s;
			len = 0;
			len = special_condition(s, c, c2);
			s += len;
			str[i++] = ft_substr(s - len, 0, len);
		}
		else
			s++;
	}
	str[i] = 0;
	return (str);
} */