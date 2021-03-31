/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarlos- <ocarlos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 16:09:30 by ocarlos-          #+#    #+#             */
/*   Updated: 2021/03/31 11:13:23 by ocarlos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
** void	ft_update_sprite(t_data *d)
**		draws the sprite on screen
** void	ft_set_sprite(t_data *d, t_pjspr *sprite, int i)
**		calculates the initial values of the sprite projection
** void	ft_sprite_projection(t_data *d, t_pjspr *sprite, int i)
**		calculates the sprite projection and prints it on screen
** void	ft_draw_sprite(t_data *d)
**		calculates sprite size and position on screen
** int	ft_find_sprite(t_data *d)
**		finds the sprite on the map
*/

void	ft_update_sprite(t_data *d)
{
	int		i;
	int		sprc;
	float	sprite_player_angle;

	i = 0;
	sprc = 0;
	while (i < SPRITE_COUNT)
	{
		sprite_player_angle = d->plr.rt_angl - ft_sprite_arctan(d, i);
		sprite_player_angle = fabs(ft_normalize_angle2(sprite_player_angle));
		if (sprite_player_angle < (d->fov / 2) + 0.2)
		{
			d->spr[i].visbl = 1;
			d->spr[i].angle = sprite_player_angle;
			d->spr[i].dstnc = ft_distance(d->spr[i].pos, d->plr.spr.pos);
			d->vsbspr[sprc++] = i;
		}
		else
			d->spr[i].visbl = 0;
		i++;
	}
}

void	ft_set_sprite(t_data *d, t_pjspr *sprite, int i)
{
	sprite->texsz = d->spr[i].txtr.size;
	sprite->h = (sprite->texsz.h / d->spr[i].dstnc) * d->dpp;
	sprite->w = (sprite->texsz.w / d->spr[i].dstnc) * d->dpp;
	sprite->topy = (d->scrsz.h / 2) - (sprite->h / 2);
	sprite->topy = (sprite->topy < 0) ? 0 : sprite->topy;
	sprite->btmy = (d->scrsz.h / 2) + (sprite->h / 2);
	sprite->btmy = (sprite->btmy > d->scrsz.h) ? d->scrsz.h : sprite->btmy;
	sprite->angle = ft_sprite_arctan(d, i) - d->plr.rt_angl;
	sprite->scrx = tan(sprite->angle) * d->dpp;
	sprite->lftx = (d->scrsz.w / 2) + sprite->scrx - (sprite->w / 2);
	sprite->rgtx = sprite->lftx + sprite->w;
	sprite->x = sprite->lftx;
}

void	ft_sprite_projection(t_data *d, t_pjspr *sprite, int i)
{
	while (sprite->x < sprite->rgtx)
	{
		sprite->txlw = (sprite->texsz.w / sprite->w);
		sprite->xofst = sprite->x - sprite->lftx;
		sprite->xofst = (sprite->xofst < 0) ? sprite->xofst * -1 : sprite->xofst;
		sprite->xofst *= sprite->txlw;
		sprite->y = sprite->topy;
		while (sprite->y < sprite->btmy)
		{
			if (!(ft_invalid_screen_area(d, (float)sprite->x, (float)sprite->y)))
			{
				sprite->dsttop = sprite->y + (sprite->h / 2) - (d->scrsz.h / 2);
				sprite->yofst = sprite->dsttop * (sprite->texsz.h / sprite->h);
				sprite->buff = (T_CL*)d->spr[i].txtr.buffer;
				sprite->color = sprite->buff[ft_pos(sprite->texsz.w, sprite->xofst, sprite->yofst)];
				if (sprite->color != d->spr[i].txtr.buffer[0])
					if (sprite->x < d->scrsz.w)
						if (d->spr[i].dstnc < d->rays[sprite->x].dist)
							d->buf[ft_pos(d->scrsz.w, sprite->x, sprite->y)] = sprite->color;
			}
			sprite->y++;
		}
		sprite->x++;
	}
}

void	ft_draw_sprite(t_data *d)
{
	int		i;
	int		j;
	t_pjspr	sprite;
	
	i = 0;
	j = 0;
	while (i < SPRITE_COUNT)
	{
		if (i == d->vsbspr[j])
		{
			ft_set_sprite(d, &sprite, i);
			ft_sprite_projection(d, &sprite, i);
			j++;
		}
		i++;
	}
}

int		ft_find_sprite(t_data *d)
{
	t_cnt	c;

	c = (t_cnt) {0};
	c.j = d->mapsz.w;
	while (c.i < SPRITE_COUNT)
	{
		while (c.y < d->mapsz.h)
		{
			c.x = 0;
			while (c.x < d->mapsz.w)
			{
				if (d->maptbl[ft_pos(c.j, c.x, c.y)] == 2)
				{
					d->spr[c.i].pos.x = c.x * d->tile.size.h;
					d->spr[c.i].pos.y = c.y * d->tile.size.w;
					return (TRUE);
				}
				c.x++;
			}
			c.y++;
		}
		c.i++;
	}
	return (FALSE);
}