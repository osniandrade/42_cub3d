/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarlos- <ocarlos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 16:09:30 by ocarlos-          #+#    #+#             */
/*   Updated: 2021/03/31 11:27:57 by ocarlos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
** void	ft_print_pixel(t_data *d, int x, int y, int color)
**		draws a pixel to the image buffer
** int	ft_drwln(t_data *d, t_pos i_pos, t_pos f_pos, int color, int rsz)
**		draws a line from i_pos to f_pos in color (Bresenham's algorithm)
**		resize = 1 - minimap pixels
**		resize = 0 - screen pixels
** int	ft_drwrt(t_data *d, t_pos pos, t_size size, int color, int rsz)
**		draws a rectangle with defined height, width and color
** void	ft_update_colorbuffer(t_data *d, t_pos pos, int color)
**		changes a pixel color in the colorbuffer
** int	ft_print_colorbuffer(t_data *d)
**		renders the color buffer and fills it with color in parameter
*/

void	ft_print_pixel(t_data *d, int x, int y, int color)
{
	char	*dst;
	
	x = round(x);
	y = round(y);
	if (y <= d->scrsz.h && x <= d->scrsz.w && x > 0 && y > 0)
	{
		dst = d->tile.addr + ((y * d->tile.ln_lngt) + (x * (d->tile.bpp / 8)));
		*(unsigned int *)dst = color;
	}
}

int		ft_drwln(t_data *d, t_pos i_pos, t_pos f_pos, int cl, int rsz)
{
	t_drwline	c;
	
	ft_init_drwstruct(&c, &i_pos, &f_pos);
	while(!(c.i_x == c.f_x && c.i_y == c.f_y))
	{
		if (rsz)
			ft_print_pixel(d, c.i_x * MAP_SCALE, c.i_y * MAP_SCALE, cl);
		else
			ft_print_pixel(d, c.i_x, c.i_y, cl);
		c.e2 = c.err;
		if (c.e2 > -c.dx)
		{
			c.err -= c.dy;
			c.i_x += c.sx;
		}
		if (c.e2 < c.dy)
		{
			c.err += c.dx;
			c.i_y += c.sy;
		}
	}
	return (TRUE);
}

int		ft_drwrt(t_data *d, t_pos pos, t_size size, int cl, int rsz)
{
	t_pos	i_pos;
	t_pos	f_pos;

	i_pos.x = pos.x;
	i_pos.y = pos.y;
	f_pos.x = pos.x + size.w;
	f_pos.y = pos.y;
	while (i_pos.y <= pos.y + size.h)
	{
		ft_drwln(d, i_pos, f_pos, cl, rsz);
		i_pos.y++;
		f_pos.y++;
	}
	return (TRUE);
}

void	ft_update_colorbuffer(t_data *d, t_pos pos, int color)
{
	t_cnt	c;

	c.x = floor(pos.x);
	c.y = floor(pos.y);
	c.i = d->scrsz.w;
	d->buf[ft_pos(c.i, c.x, c.y)] = color;
}

int		ft_print_colorbuffer(t_data *d)
{
	t_cnt	c;

	c.x = 0;
	c.i = d->scrsz.w;
	while (c.x < d->scrsz.w)
	{
		c.y = 0;
		while (c.y < d->scrsz.h)
		{
			ft_print_pixel(d, c.x, c.y, d->buf[ft_pos(c.i, c.x, c.y)]);
			c.y++;
		}
		c.x++;
	}
	return (TRUE);
}