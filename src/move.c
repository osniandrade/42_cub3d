/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarlos- <ocarlos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 16:09:30 by ocarlos-          #+#    #+#             */
/*   Updated: 2021/03/30 16:08:35 by ocarlos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
** int	ft_move_player(t_data *d)
**		updates player positions and directions
** int	ft_player_direction(t_data *d)
**		gets player moving direction and speed
*/

int		ft_move_player(t_data *d)
{
	float	movestep;
	float	playerCos;
	float	playerSin;
	t_pos	newplayer;

	d->plr.rt_angl += d->plr.turndir * d->plr.turnspd;
	d->plr.rt_angl = ft_normalize_angle(d->plr.rt_angl);
	movestep = d->plr.walkdir * d->plr.walkspd;
	playerCos = cos(d->plr.rt_angl) * movestep;
	playerSin = sin(d->plr.rt_angl) * movestep;
	if (d->plr.strafe == TRUE)
	{
		newplayer.x = d->plr.spr.pos.x - playerSin;
		newplayer.y = d->plr.spr.pos.y + playerCos;
	}
	else
	{
		newplayer.x = d->plr.spr.pos.x + playerCos;
		newplayer.y = d->plr.spr.pos.y + playerSin;
	}	
	if (!(ft_invalid_map_position(d, newplayer.x, newplayer.y)))
	{
		d->plr.spr.pos.x = newplayer.x;
		d->plr.spr.pos.y = newplayer.y;
	}
	return (TRUE);
}

int		ft_player_direction(t_data *d)
{
	d->plr.strafe = 0;
	if (d->dir.l == TRUE)
		d->plr.turndir = -MOVESPEED;
	if (d->dir.r == TRUE)
		d->plr.turndir = +MOVESPEED;
	if (d->dir.u == TRUE)
		d->plr.walkdir = +MOVESPEED;
	if (d->dir.d == TRUE)
		d->plr.walkdir = -MOVESPEED;
	if (d->dir.sl == TRUE)
	{
		d->plr.walkdir = -MOVESPEED;
		d->plr.strafe = TRUE;
	}
	if (d->dir.sr == TRUE)
	{
		d->plr.walkdir = +MOVESPEED;
		d->plr.strafe = TRUE;
	}
	if (d->dir.u == FALSE && d->dir.d == FALSE && 
		d->dir.sl == FALSE && d->dir.sr == FALSE)
		d->plr.walkdir = 0;
	if (d->dir.l == FALSE && d->dir.r == FALSE)
		d->plr.turndir = 0;
	return (TRUE);
}
