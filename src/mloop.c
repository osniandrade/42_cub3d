/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mloop.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarlos- <ocarlos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 16:09:30 by ocarlos-          #+#    #+#             */
/*   Updated: 2021/03/30 15:24:29 by ocarlos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
** void	ft_setup(t_data *d)
**      initializes the setup for the main loop
** int	ft_update(t_data *d)
**      moves the image in the window
** int	ft_draw(t_data *d)
**      draws elements in the window
*/

void	ft_setup(t_data *d)
{
	ft_init_win(d);
	ft_clear_colorbuffer(d, 1);
	ft_init_img(d);
	ft_init_sprite_struct(d);
	ft_load_file_paths(d);
	ft_load_xpm_texture(d);
	ft_load_xpm_sprite(d);
	ft_loadmap(d);
	ft_loadcolors(d);
	ft_init_player(d);
	ft_find_sprite(d);
}

int		ft_update(t_data *d)
{
	ft_clear_colorbuffer(d, 0);
	ft_reset_array(d->vsbspr, SPRITE_COUNT);
	ft_update_sprite(d);
	ft_player_direction(d);
	ft_cast_all_rays(d);
	ft_move_player(d);
	ft_gen_3d_proj(d);
	return (TRUE);
}

int		ft_draw(t_data *d)
{
	ft_draw_sprite(d);
	ft_print_colorbuffer(d);
	if (d->cub.bmp == 1)
		ft_save_img(d);
	mlx_put_image_to_window(d->mlx, d->mlx_win, d->tile.img, 0, 0);
	return (TRUE);
}