/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumorale <lumorale@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 12:34:20 by lumorale          #+#    #+#             */
/*   Updated: 2023/04/07 15:16:07 by lumorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

static char	*strjoin_free(char *s1, char *s2, int n)
{
	char	*str;
	int		s1len;

	s1len = ft_strlen(s1);
	str = malloc(sizeof(char) * (s1len + n + 1));
	if (!str)
		return (0);
	ft_memcpy(str, s1, s1len);
	ft_memcpy(&str[s1len], s2, n);
	str[s1len + n] = 0;
	free(s1);
	return (str);
}

char	*ft_next_line(char *str)
{
	int		i;
	int		j;
	char	*new_line;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
	{
		free(str);
		return (0);
	}
	new_line = ft_calloc(sizeof(char), ft_strlen(str) - i + 1);
	i++;
	j = 0;
	while (str[i])
		new_line[j++] = str[i++];
	free(str);
	return (new_line);
}

char	*ft_get_line(char *str)
{
	char	*tmp;
	int		i;

	i = 0;
	if (!str[i])
		return (0);
	while (str[i] && str[i] != '\n')
		i++;
	tmp = ft_calloc(sizeof(char), i + 2);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		tmp[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
		tmp[i] = '\n';
	return (tmp);
}

char	*ft_read_file(int fd, char *str)
{
	char	*buffer;
	int		readed;

	if (!str)
		str = ft_calloc(sizeof(char), 1);
	buffer = ft_calloc(sizeof(char), BUFFER_SIZE + 1);
	readed = 1;
	while (readed > 0)
	{
		readed = read(fd, buffer, BUFFER_SIZE);
		if (readed <= 0)
			break ;
		str = strjoin_free(str, buffer, readed);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(buffer);
	if (readed == -1)
	{
		free(str);
		return (0);
	}
	return (str);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*str;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	str = ft_read_file(fd, str);
	if (!str)
		return (0);
	line = ft_get_line(str);
	str = ft_next_line(str);
	return (line);
}
