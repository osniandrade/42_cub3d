/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarlos- <ocarlos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 16:09:30 by ocarlos-          #+#    #+#             */
/*   Updated: 2021/03/30 17:15:31 by ocarlos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
** int	*ft_setnull(int *i)
**		side function of ft_split
** char	**ft_split(char const *s, char c)
**		splits a string using 'c' char as separator
** int	ft_isdigit(int c)
**		checks if 'c' character is numeric
** int	ft_tstspc(const char ch)
**		checks if 'ch' character is any kind of blank space
** int	ft_atoi(const char *str)
**		converts a numeric char to integer
*/

int		*ft_setnull(int *i)
{
	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	return (0);
}

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
	free(temp);
	result[i[1]] = NULL;
	return (result);
}

int		ft_isdigit(int c)
{
	if ((c >= 48) && (c <= 57))
		return (1);
	else
		return (0);
}

int		ft_tstspc(const char ch)
{
	if ((ch == ' ') || (ch == '\f') || (ch == '\n') ||
		(ch == '\r') || (ch == '\t') || (ch == '\v'))
		return (1);
	return (0);
}

int		ft_atoi(const char *str)
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
