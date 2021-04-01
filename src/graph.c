/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarlos- <ocarlos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 16:09:30 by ocarlos-          #+#    #+#             */
/*   Updated: 2021/04/01 16:24:27 by ocarlos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
** void	ft_print_pixel(t_data *d, int x, int y, int color)
**		draws a pixel to the image buffer
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
