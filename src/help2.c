/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarlos- <ocarlos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 16:09:30 by ocarlos-          #+#    #+#             */
/*   Updated: 2021/04/01 16:59:58 by ocarlos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
** float	ft_dst(t_pos coord_a, t_pos coord_b)
**		calculates the distance between two coordinates x and y
** void	ft_reset_array(int *array, int i)
**		resets every position in the array to 0
** int	ft_pos(int w, int x, int y)
**		converts x and y coordinates to 2d array position
*/

float	ft_dst(t_pos coord_a, t_pos coord_b)
{
	t_pos	rslt;

	rslt.x = coord_b.x - coord_a.x;
	rslt.x *= rslt.x;
	rslt.y = coord_b.y - coord_a.y;
	rslt.y *= rslt.y;
	return (sqrt(rslt.x + rslt.y));
}

void	ft_reset_array(int *array, int i)
{
	while (i >= 0)
		array[i--] = 9999;
}

int		ft_pos(int w, int x, int y)
{
	return ((w * y) + x);
}
