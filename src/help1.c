/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarlos- <ocarlos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 16:09:30 by ocarlos-          #+#    #+#             */
/*   Updated: 2021/04/01 17:22:55 by ocarlos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
** float	ft_normalize_angle(float angle)
**		normalize angle between 0 and 360
** float	ft_normalize_angle2(float angle)
**		normalize angle between 0 and 180
** float	ft_sprite_arctan(t_data *d, int i)
**		gets the arc tangent of a sprite relative to player position
*/

float	ft_normalize_angle(float angle)
{
	angle = remainder(angle, PI * 2);
	if (angle < 0)
		angle = (2 * PI) + angle;
	return (angle);
}

float	ft_normalize_angle2(float angle)
{
	if (angle > PI)
		angle -= PI * 2;
	if (angle < -PI)
		angle += PI * 2;
	return (angle);
}

float	ft_sprite_arctan(t_data *d, int i)
{
	t_pos		sprite;
	t_pos		player;
	t_size		sprsize;

	sprite = d->spr[i].pos;
	player = d->plr.spr.pos;
	sprsize = d->spr[i].txtr.size;
	return (atan2(
			(sprite.y + (sprsize.h / 2)) - player.y,
			(sprite.x + (sprsize.w / 2)) - player.x));
}
