/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarlos- <ocarlos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 16:09:30 by ocarlos-          #+#    #+#             */
/*   Updated: 2021/03/30 15:09:24 by ocarlos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
** void	ft_load_file_paths(t_data *d)
**      loads texture paths from file to struct
** void	ft_load_xpm_texture(t_data *d)
**      loads xpm texture file into code
** void	ft_load_xpm_sprite(t_data *d)
**      loads sprite textures from array to a new image
** int	ft_loadmap(t_data *d)
**      loads map into data structure
** int	ft_loadcolors(t_data *d)
**      loads ceiling and floor colors to struct
*/

void	ft_load_file_paths(t_data *d)
{
	int i = 0;

	while (i < TEXTURE_COUNT)
    {
		d->txt[i].path = d->cub.txpath[i];
        i++;
    }
	i = 0;
	while (i < SPRITE_COUNT)
    {
		d->spr[i].txtr.path = d->cub.sppath[i];
        i++;
    }
}

void	ft_load_xpm_texture(t_data *d)
{
	int i = 0;

	while (i < TEXTURE_COUNT)
	{
		d->txt[i].instc.img = mlx_xpm_file_to_image(
			d->mlx, 
			d->txt[i].path, 
			&d->txt[i].size.w, 
			&d->txt[i].size.h
		);
		d->txt[i].instc.addr = mlx_get_data_addr(
			d->txt[i].instc.img, 
			&(d->txt[i].instc.bpp), 
			&(d->txt[i].instc.ln_lngt), 
			&(d->txt[i].instc.endian)
		);
		d->txt[i].buffer = (t_cl *) d->txt[i].instc.addr;
		i++;
	}
}

void	ft_load_xpm_sprite(t_data *d)
{
	int	i = 0;

	while (i < SPRITE_COUNT)
	{
		d->spr[i].txtr.instc.img = mlx_xpm_file_to_image(
			d->mlx,
			d->spr[i].txtr.path,
			&d->spr[i].txtr.size.w,
			&d->spr[i].txtr.size.h
		);
		d->spr[i].txtr.instc.addr = mlx_get_data_addr(
			d->spr[i].txtr.instc.img,
			&(d->spr[i].txtr.instc.bpp),
			&(d->spr[i].txtr.instc.ln_lngt),
			&(d->spr[i].txtr.instc.endian)
		);
		d->spr[i].txtr.buffer = (t_cl*)d->spr[i].txtr.instc.addr;
		i++;
	}
}

int		ft_loadmap(t_data *d)
{
	t_cnt c;

	c = (t_cnt) {0};
	ft_init_map_size(d);
	c.i = d->mapsz.w;
	while (c.y < d->mapsz.h)
	{
		while (c.x < d->mapsz.w)
		{
			d->maptbl[ft_pos(c.i, c.x, c.y)] = d->cub.map[ft_pos(c.i, c.x, c.y)];
			c.x++;
		}
		c.x = 0;
		c.y++;
	}
	return (TRUE);
}

int		ft_loadcolors(t_data *d)
{
	d->f_clr = ft_crt_trgb(
		255,
		d->cub.rgbdw[0],
		d->cub.rgbdw[1],
		d->cub.rgbdw[2]
	);
	d->c_clr = ft_crt_trgb(
		255,
		d->cub.rgbup[0],
		d->cub.rgbup[1],
		d->cub.rgbup[2]
	);
	return (TRUE);
}
