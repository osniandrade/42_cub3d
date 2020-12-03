/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarlos- <ocarlos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 16:51:46 by ocarlos-          #+#    #+#             */
/*   Updated: 2020/12/02 14:51:39 by ocarlos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFFER_SIZE 32

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

typedef struct	s_lndata
{
	int		ret;
	int		fd;
	char	*buf;
	char	*s;
}				t_lndata;
char			*ft_strjoin(char *s1, char *s2);
size_t			ft_strlen(const char *s);
int				ft_strchr(char *s);
char			*ft_strdup(char *s1);
int				get_next_line(int fd, char **line);
char			*ft_getln(char *s);
char			*ft_getst(char *s);
void			ft_memfix(char *tmp, char *s, char *buf);
t_lndata		ft_mainloop(t_lndata ln);

#endif
