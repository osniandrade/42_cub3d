/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarlos- <ocarlos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 16:09:30 by ocarlos-          #+#    #+#             */
/*   Updated: 2021/03/30 17:13:16 by ocarlos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
** size_t	ft_strlen(const char *s)
**		returns the size of a string
** void	*ft_memcpy(void *dest, const void *src, size_t n)
**		copies n characters of a memory address to another
** char	*ft_strdup(const char *s1)
**		duplicates the content of a memory address to a new allocated address
** char	**ft_setarray(char *temp, char ch)
**		side function of ft_split
** int	*ft_setdelim(char *temp, char ch)
**		side function of ft_split
*/

size_t	ft_strlen(const char *s)
{
	size_t			i;

	i = 0;
	if (*s == '\0')
		return (0);
	while (*s++ != '\0')
		i++;
	return (i);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char			*d;
	const char		*s;

	d = dest;
	s = src;
	if (!s && !d)
		return (NULL);
	while (n--)
		*d++ = *s++;
	return (dest);
}

char	*ft_strdup(const char *s1)
{
	char			*dst;
	int				size;

	size = ft_strlen(s1);
	if (!(dst = malloc(size + 1)))
		return (NULL);
	ft_memcpy(dst, s1, size);
	dst[size] = '\0';
	return (dst);
}

char	**ft_setarray(char *temp, char ch)
{
	int				words;
	int				i;
	int				size;

	i = 0;
	words = 0;
	size = (temp) ? ft_strlen(temp) : 0;
	while (temp[i] != '\0' && i < size)
	{
		if (temp[i] != ch)
		{
			words++;
			while (temp[i] != ch && temp[i + 1] != '\0')
				i++;
		}
		i++;
	}
	return ((char **)malloc(sizeof(char *) * (words + 1)));
}

int		*ft_setdelim(char *temp, char ch)
{
	int				i;

	i = 0;
	while (temp[i] != '\0')
	{
		if (temp[i] == ch)
			temp[i] = '\0';
		i++;
	}
	return (0);
}
