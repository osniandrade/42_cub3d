/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarlos- <ocarlos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 16:46:24 by ocarlos-          #+#    #+#             */
/*   Updated: 2021/03/14 10:59:59 by ocarlos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>

size_t		ft_gnl_strlen(const char *s)
{
	size_t		i;

	i = 0;
	if (!s || *s == '\0')
		return (0);
	while (*s++)
		i++;
	return (i);
}

char		*ft_gnl_strjoin(char *s1, char *s2)
{
	char	*result;
	char	*ret;
	char	*refs1;
	int		total;
	int		i[2];

	if (!s1 && !s2)
		return (NULL);
	refs1 = s1;
	i[0] = ft_gnl_strlen((char *)s1);
	i[1] = ft_gnl_strlen((char *)s2);
	total = (i[0] + i[1] + 1);
	if (!(result = (char *)malloc(sizeof(char) * total)))
		return (NULL);
	ret = result;
	while (i[0]--)
		*result++ = *s1++;
	while (i[1]--)
		*result++ = *s2++;
	*result = '\0';
	if (refs1)
		free(refs1);
	return (ret);
}

int			ft_gnl_strchr(char *s)
{
	int i;
	int size;

	size = ft_gnl_strlen(s);
	i = (size <= BUFFER_SIZE) ? 0 : size - BUFFER_SIZE;
	if (!s)
		return (0);
	while (s[i] != '\n' && s[i] != '\0')
		i++;
	if (s[i] == '\n')
		return (1);
	return (0);
}

char		*ft_gnl_strdup(char *s1)
{
	char	*s2;
	char	*str;

	s2 = (char *)malloc(sizeof(char) * (ft_gnl_strlen(s1) + 1));
	str = s2;
	while (*s1)
		*s2++ = *s1++;
	*s2 = '\0';
	return (str);
}
