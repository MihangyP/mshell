/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: traveloa <traveloa@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 08:12:24 by traveloa          #+#    #+#             */
/*   Updated: 2024/09/26 08:12:26 by traveloa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>

char	*get_next_line(int fd);
char	*gnl_ft_strcpy(char *src);
char	*gnl_ft_strjoin(char *s1, char *s2);
int		gnl_ft_strchr(const char *s, char c);
size_t	gnl_ft_strlen(const char *s);
void	*gnl_ft_calloc(size_t nmemb, size_t size);
char	*get_line(char *str);
char	*get_rest(char *str);
#endif
