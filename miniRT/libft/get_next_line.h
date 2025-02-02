/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 19:26:54 by bposa             #+#    #+#             */
/*   Updated: 2024/12/24 22:07:56 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include "libft.h"
# include <unistd.h>
# include <stdlib.h>

char	*get_next_line(int fd, int *error);
size_t	my_strlen(const char *s);
void	*my_memcpy(void *dst, const void *src, size_t n);
void	my_bzero(char *s);

#endif