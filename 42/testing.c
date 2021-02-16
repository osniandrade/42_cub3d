/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarlos- <ocarlos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 13:44:25 by ocarlos-          #+#    #+#             */
/*   Updated: 2021/02/16 15:12:12 by ocarlos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


// tests line drawing function
int		ft_test_line_draw(t_data *data)
{
	t_coord	i_pos, f_pos;
	int		center = 128;
	int		incr = 64;

	i_pos.x = center;
	i_pos.y = center;

	// horizontal right
	f_pos.x = center + incr;
	f_pos.y = center;
	ft_draw_line(data, i_pos, f_pos, ft_crt_trgb(0, 255, 0, 255));

	// diagonal up right
	f_pos.x = center + incr;
	f_pos.y = center + incr;
	ft_draw_line(data, i_pos, f_pos, ft_crt_trgb(0, 255, 0, 255));

	// vertical up
	f_pos.x = center;
	f_pos.y = center - incr;
	ft_draw_line(data, i_pos, f_pos, ft_crt_trgb(0, 255, 0, 255));

	// diagonal up left
	f_pos.x = center - incr;
	f_pos.y = center - incr;
	ft_draw_line(data, i_pos, f_pos, ft_crt_trgb(0, 255, 0, 255));

	// horizontal left
	f_pos.x = center - incr;
	f_pos.y = center;
	ft_draw_line(data, i_pos, f_pos, ft_crt_trgb(0, 255, 0, 255));

	// diagonal down left
	f_pos.x = center - incr;
	f_pos.y = center + incr;
	ft_draw_line(data, i_pos, f_pos, ft_crt_trgb(0, 255, 0, 255));

	// vertical down
	f_pos.x = center;
	f_pos.y = center + incr;
	ft_draw_line(data, i_pos, f_pos, ft_crt_trgb(0, 255, 0, 255));

	// diagonal down right
	f_pos.x = center + incr;
	f_pos.y = center - incr;
	ft_draw_line(data, i_pos, f_pos, ft_crt_trgb(0, 255, 0, 255));

	mlx_put_image_to_window(data->mlx, data->mlx_win, data->tile.img, 0, 0);
	return (TRUE);
}

// moves player to test collision with walls
int     ft_test_collision(t_data *data)
{
    if (!(ft_invalid_area(data, data->player.playerspr.pos.x, data->player.playerspr.pos.y)))
		data->player.walkDirection = +MOVESPEED;
		data->player.turnDirection = +MOVESPEED;
    
    return (TRUE);
}

// generates texture for walls
int		ft_texture_gen(t_data *data, int pos)
{
  data->textures[pos] = (uint32_t*) malloc(sizeof(uint32_t) * (uint32_t)SCREENW * (uint32_t)SCREENH);
	for (int x = 0; x < TEXTURE_W; x++)
	{
		for (int y = 0; y < TEXTURE_H; y++)
		{
			if (x % 8 && y % 8)
				data->textures[pos][(SCREENW * y) + x] = ft_crt_trgb(255, 0, 0, 0);
			else
				data->textures[pos][(SCREENW * y) + x] = ft_crt_trgb(255, 0, 128, 0);
		}
	}
  return (TRUE);
}