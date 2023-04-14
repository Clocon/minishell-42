/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumorale <lumorale@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 12:34:33 by lumorale          #+#    #+#             */
/*   Updated: 2023/04/04 16:22:23 by lumorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include "../../libft/includes/libft.h"

char	*get_next_line(int fd);
char	*ft_next_line(char *str);
char	*ft_get_line(char *str);
char	*ft_read_file(int fd, char *str);

#endif