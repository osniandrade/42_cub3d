/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarlos- <ocarlos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 16:09:30 by ocarlos-          #+#    #+#             */
/*   Updated: 2021/04/09 14:45:16 by ocarlos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
** int	ft_argnumber(char **clean_line)
**		references the arg letter to its number
** int	ft_loadedargs(t_file *file, int key, int flag)
**		loads an array with already read arguments or
**		returns if all alguments were read from file
**		0 = R
**		1 = NO
**		2 = SO
**		3 = WE
**		4 = EA
**		5 = S
**		6 = C
**		7 = F
**		key -> argument to flag as read
**		flag = 0 -> reads argument
**		flag = 1 -> returns if all alguments were read
*/

int		ft_argnumber(char **clean_line)
{
	if (ft_strncmp(clean_line[0], "R", 1) == 0)
		return (0);
	if (ft_strncmp(clean_line[0], "NO", 2) == 0)
		return (1);
	if (ft_strncmp(clean_line[0], "SO", 2) == 0)
		return (2);
	if (ft_strncmp(clean_line[0], "WE", 2) == 0)
		return (3);
	if (ft_strncmp(clean_line[0], "EA", 2) == 0)
		return (4);
	if (ft_strncmp(clean_line[0], "S", 1) == 0)
		return (5);
	if (ft_strncmp(clean_line[0], "C", 1) == 0)
		return (6);
	if (ft_strncmp(clean_line[0], "F", 1) == 0)
		return (7);
	return (FALSE);
}

int		ft_loadedargs(t_file *file, int key, int flag)
{
	int i;

	i = 0;
	if (flag == 0)
	{
		file->args[key] = 1;
		return (TRUE);
	}
	if (flag == 1)
	{
		while (i < 8)
			if (file->args[i++] == 0)
				return (FALSE);
		return (TRUE);
	}
	return (FALSE);
}
