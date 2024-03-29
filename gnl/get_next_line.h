/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 17:41:55 by mkong             #+#    #+#             */
/*   Updated: 2024/01/23 14:39:57 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif
# include <unistd.h>
# include <stdlib.h>

char	*get_next_line(int fd);
size_t	check_nl(char *buf);
size_t	ft_strlen_gnl(const char *s);
char	*ft_strnjoin(char *s1, char const *s2, size_t n);
char	*ft_strndup(const char *s1, size_t n);

typedef struct s_node
{
	int				fd;
	char			*buf;
	size_t			idx;
}				t_node_;

#endif
