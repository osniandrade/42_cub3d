/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarlos- <ocarlos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 09:29:52 by ocarlos-          #+#    #+#             */
/*   Updated: 2021/03/24 16:26:02 by ocarlos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*******************************************************************************
 * COLOR HANDLING FUNCTIONS
 *******************************************************************************/

// returns a color in hexadecimal format to use in minilibx
uint32_t	ft_crt_trgb(int t, int r, int g, int b)
{
	return(t << 24 | r << 16 | g << 8 | b);
}

// gets a color in minilibx format and returns its transparency
uint32_t	ft_get_t(int trgb)
{
	return (trgb & (0xFF << 24));
}

// gets a color in minilibx format and returns its red value
uint32_t	ft_get_r(int trgb)
{
	return (trgb & (0xFF << 16));
}

// gets a color in minilibx format and returns its green value
uint32_t	ft_get_g(int trgb)
{
	return (trgb & (0xFF << 8));
}

// gets a color in minilibx format and returns its blue value
uint32_t	ft_get_b(int trgb)
{
	return (trgb & 0xFF);
}

/*******************************************************************************
 * LIBFT FUNCTIONS
 *******************************************************************************/

// returns the size of a string
size_t		ft_strlen(const char *s)
{
	size_t		i;

	i = 0;
	if (*s == '\0')
		return (0);
	while (*s++ != '\0')
		i++;
	return (i);
}

// copies n characters of a memory address to another
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

// duplicates the content of a memory address to a new allocated address
char	*ft_strdup(const char *s1)
{
	char	*dst;
	int		size;

	size = ft_strlen(s1);
	if (!(dst = malloc(size + 1)))
		return (NULL);
	ft_memcpy(dst, s1, size);
	dst[size] = '\0';
	return (dst);
}

// side function of ft_split
char	**ft_setarray(char *temp, char ch)
{
	int		words;
	int		i;
	int		size;

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

// side function of ft_split
int		*ft_setdelim(char *temp, char ch)
{
	int		i;

	i = 0;
	while (temp[i] != '\0')
	{
		if (temp[i] == ch)
			temp[i] = '\0';
		i++;
	}
	return (0);
}

// side function of ft_split
int		*ft_setnull(int *i)
{
	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	return (0);
}

// splits a string using 'c' char as separator
char	**ft_split(char const *s, char c)
{
	char	**result;
	char	*temp;
	int		i[3];

	temp = (s) ? ft_strdup(s) : NULL;
	if (!s || !c || !temp || !(result = ft_setarray(temp, c)))
		return (NULL);
	ft_setnull(i);
	i[0] = (temp) ? ft_strlen(temp) : 0;
	ft_setdelim(temp, c);
	while (i[2] < i[0])
	{
		if (temp[i[2]] == '\0')
			i[2]++;
		else
		{
			if (!(result[i[1]] = ft_strdup(&temp[i[2]])))
				return (NULL);
			i[1]++;
			i[2] += ft_strlen(&temp[i[2]]);
		}
	}
	result[i[1]] = NULL;
	return (result);
}

// checks if 'c' character is numeric
int				ft_isdigit(int c)
{
	if ((c >= 48) && (c <= 57))
		return (1);
	else
		return (0);
}

// checks if 'ch' character is any kind of blank space
int		ft_tstspc(const char ch)
{
	if ((ch == ' ') || (ch == '\f') || (ch == '\n') ||
		(ch == '\r') || (ch == '\t') || (ch == '\v'))
		return (1);
	return (0);
}

// converts a numeric char to integer
int				ft_atoi(const char *str)
{
	int		signal;
	int		num;

	signal = 1;
	num = 0;
	while (ft_tstspc(*str))
		str++;
	if ((*str == '+') || (*str == '-'))
		if (*str++ == '-')
			signal *= -1;
	if (!(ft_isdigit(*str)))
		return (0);
	while (ft_isdigit(*str))
		num = num * 10 + (*str++ - 48);
	return (num * signal);
}

// compares the n characters of 2 strings
int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int		i;

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

// checks if character 'c' is present in string 's'
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

// checks if character 'c' is an ASCII value
int		ft_isascii(int c)
{
	if ((c >= 0) && (c <= 127))
		return (1);
	else
		return (0);
}

// fills a string with '0'
void	*ft_bzero(void *s, size_t n)
{
	char	*start;

	start = s;
	while (n--)
		*start++ = 0;
	return (s);
}