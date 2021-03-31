/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarlos- <ocarlos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 16:09:30 by ocarlos-          #+#    #+#             */
/*   Updated: 2021/03/30 17:17:50 by ocarlos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
** int	ft_strncmp(const char *s1, const char *s2, size_t n)
**		compares the n characters of 2 strings
** char	*ft_strchr(const char *s, int c)
**		checks if character 'c' is present in string 's'
** int	ft_isascii(int c)
**		checks if character 'c' is an ASCII value
** void	*ft_bzero(void *s, size_t n)
**		fills a string with '0'
*/

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	while (!((s1[i] == '\0') && (s2[i] == '\0')) && (i < n))
	{
		if (s1[i] != s2[i])
		{
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		}
		i++;
	}
	return (0);
}

char	*ft_strchr(const char *s, int c)
{
	char			*sfer;

	sfer = (char *)s;
	while (*sfer != '\0')
		if (*sfer++ == (char)c)
			return (--sfer);
	if ((c == '\0') && (*sfer == '\0'))
		return (sfer);
	return (0);
}

int		ft_isascii(int c)
{
	if ((c >= 0) && (c <= 127))
		return (1);
	else
		return (0);
}

void	*ft_bzero(void *s, size_t n)
{
	char			*start;

	start = s;
	while (n--)
		*start++ = 0;
	return (s);
}
