/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarlos- <ocarlos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 16:09:30 by ocarlos-          #+#    #+#             */
/*   Updated: 2021/03/30 16:05:11 by ocarlos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
** int	ft_invalid_screen_area(t_data *d, float x, float y)
**      checks if image is in drawable area, uses "step" as increment
** int	ft_invalid_map_position(t_data *d, float x, float y)
**      checks if screen position is valid
** int	ft_invalid_area(t_data *d, float x, float y)
**      checks both screen and map position
*/

int		ft_invalid_screen_area(t_data *d, float x, float y)
{
	if (x < 0 || x > d->scrsz.w || y < 0  || y > d->scrsz.h)
		return (TRUE);
	else
		return (FALSE);
}

int		ft_invalid_map_position(t_data *d, float x, float y)
{
	t_cnt   c;

	c.x = floor(x / d->tile.size.w);
	c.y = floor(y / d->tile.size.w);
	c.i = d->mapsz.w;
	if (d->maptbl[ft_pos(c.i, c.x, c.y)] != 0)
		return (TRUE);
	else
		return (FALSE);
}

int		ft_invalid_area(t_data *d, float x, float y)
{
	if (ft_invalid_screen_area(d, x, y))
		return (TRUE);
	if (ft_invalid_map_position(d, x / TILE_SIZE, y / TILE_SIZE))
		return (TRUE);
	else
		return (FALSE);
}
