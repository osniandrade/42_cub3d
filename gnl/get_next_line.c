/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarlos- <ocarlos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 12:07:56 by ocarlos-          #+#    #+#             */
/*   Updated: 2021/03/14 10:59:39 by ocarlos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
** A function which returns a line read from a file descriptor,
** without the newline
**
** RETURN VALUES
**  1 : A line has been read
**  0 : EOF has been reached
** -1 : An error happened
*/

char		*ft_getln(char *s)
{
	int		i;
	char	*str;
	char	*rstr;

	i = 0;
	while (s[i] != '\n' && s[i] != '\0')
		i++;
	if (!(str = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	rstr = str;
	while (i--)
		*str++ = *s++;
	*str = '\0';
	return (rstr);
}

char		*ft_getst(char *s)
{
	char	*str;

	while (*s != '\n' && *s != '\0')
		s++;
	if (*s != '\0')
		s++;
	str = ft_gnl_strdup(s);
	return (str);
}

t_lndata	ft_mainloop(t_lndata ln)
{
	while ((ft_gnl_strchr(ln.s)) != 1 && ln.ret != 0)
	{
		if ((ln.ret = read(ln.fd, ln.buf, BUFFER_SIZE)) == -1)
		{
			free(ln.buf);
			ln.ret = -1;
			return (ln);
		}
		ln.buf[ln.ret] = '\0';
		ln.s = ft_gnl_strjoin(ln.s, ln.buf);
	}
	free(ln.buf);
	return (ln);
}

int			get_next_line(int fd, char **line)
{
	static t_lndata	ln;
	char			*tmp;

	ln.ret = 1;
	ln.fd = fd;
	if (!line || ln.fd < 0 || BUFFER_SIZE <= 0)
		return (-1);
	if (!(ln.buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	ln = ft_mainloop(ln);
	if (ln.ret == -1)
		return (-1);
	*line = ft_getln(ln.s);
	tmp = ln.s;
	if (ln.ret == 0)
	{
		free(ln.s);
		ln.s = NULL;
		return (0);
	}
	ln.s = ft_getst(ln.s);
	free(tmp);
	return (1);
}
