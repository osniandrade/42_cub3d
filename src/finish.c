/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarlos- <ocarlos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 16:09:30 by ocarlos-          #+#    #+#             */
/*   Updated: 2021/04/01 16:37:45 by ocarlos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
** void	t_destroy_images(t_data *d)
**		frees texture memory allocations
** void	ft_destroy(t_data *d, int f)
**		finishes the program
**		f = 0 - used before creation of color and map buffers
**		f = 1 - used anytime after first image created
*/

void	ft_destroy_images(t_data *d)
{
	int		i;

	i = 0;
	mlx_destroy_image(d->mlx, d->tile.img);
	while (i < TEXTURE_COUNT)
	{
		mlx_destroy_image(d->mlx, d->txt[i].instc.img);
		i++;
	}
	i = 0;
	while (i < SPRITE_COUNT)
	{
		mlx_destroy_image(d->mlx, d->spr[i].txtr.instc.img);
		i++;
	}
}

void	ft_destroy(t_data *d, int f)
{
	free(d->cub.txpath[0]);
	free(d->cub.txpath[1]);
	free(d->cub.txpath[2]);
	free(d->cub.txpath[3]);
	free(d->cub.sppath[0]);
	free(d->cub.map);
	if (f == 0)
		exit(0);
	free(d->buf);
	free(d->maptbl);
	free(d->rays);
	ft_destroy_images(d);
	mlx_destroy_window(d->mlx, d->mlx_win);
	exit(0);
}
