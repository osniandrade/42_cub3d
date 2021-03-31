/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarlos- <ocarlos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 16:09:30 by ocarlos-          #+#    #+#             */
/*   Updated: 2021/03/31 11:19:05 by ocarlos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
** int  ft_init_win(t_data *d)
**		initializes the main struct variables
** void ft_init_img(t_data *d)
**		initializes a new image's struct
** void ft_init_map_size(t_data *d)
**		initializes the map size
** void	ft_init_player(t_data *d)
**		initializes player data
*/

int		ft_init_win(t_data *d)
{
	t_cnt c;
	
	d->mlx = mlx_init();
	mlx_get_screen_size(d->mlx, &c.x, &c.y);
	if (c.x < d->cub.scrsize.w || c.y < d->cub.scrsize.h)
	{
		d->cub.scrsize.w = c.x;
		d->cub.scrsize.h = c.y;
	}
	d->gamespd = (((float)d->cub.scrsize.h) / (float)c.y) * GAMESPEED;
	d->scrsz.w = d->cub.scrsize.w;
	d->scrsz.h = d->cub.scrsize.h;
	c.i = d->scrsz.w;
	c.j = d->scrsz.h;
	d->fov = (60 * (PI / 180));
	d->dpp = (c.i / 2) / tan(d->fov / 2);
	d->n_rays = c.i;
	d->rays = malloc(sizeof(t_rays) * d->n_rays);
	d->mlx_win = mlx_new_window(d->mlx, c.i, c.j, "CUB3D");
	return (TRUE);
}

void	ft_init_img(t_data *d)
{
	t_img	img;

	img.img = mlx_new_image(d->mlx, d->scrsz.w, d->scrsz.h);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, 
									&img.ln_lngt, &img.endian);
	img.pos.x = 0;
	img.pos.y = 0;
	img.size.w = TILE_SIZE;
	img.size.h = TILE_SIZE;
	d->tile = img;
}

void	ft_init_map_size(t_data *d)
{
	d->mapsz.h = d->cub.mapsize.h;
	d->mapsz.w = d->cub.mapsize.w;
	d->maptbl = malloc(d->mapsz.w * d->mapsz.h * sizeof(int));
}

void	ft_init_player(t_data *d)
{
	d->plr.spr.pos.x = d->cub.strtpos.x;
	d->plr.spr.pos.y = d->cub.strtpos.y;
	d->plr.turndir = 0;
	d->plr.walkdir = 0;
	if (d->cub.plrdir == 'N')
		d->plr.rt_angl = PI * 1.5;
	if (d->cub.plrdir == 'S')
		d->plr.rt_angl = PI * 0.5;
	if (d->cub.plrdir == 'E')
		d->plr.rt_angl = PI * 2;
	if (d->cub.plrdir == 'W')
		d->plr.rt_angl = PI;
	d->plr.walkspd = INIT_WALKSPD * d->gamespd;
	d->plr.turnspd = INIT_TURNSPD * (PI / 180) * d->gamespd;
}
