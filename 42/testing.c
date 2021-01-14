/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarlos- <ocarlos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 13:44:25 by ocarlos-          #+#    #+#             */
/*   Updated: 2021/01/13 17:57:59 by ocarlos-         ###   ########.fr       */
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

int     ft_test_collision(t_data *data)
{
    if (ft_validarea(data, MOVESPEED))
		data->player.walkDirection++;
    
    return (TRUE);
}