/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarlos- <ocarlos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 16:09:36 by ocarlos-          #+#    #+#             */
/*   Updated: 2021/02/03 12:26:26 by ocarlos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// main loop - draws and moves the image
int		main_loop(t_data *data)
{
	//ft_erase(data);
	ft_move(data);
	//ft_raycast(data);
	ft_draw(data);
	//ft_update(data);
	return (TRUE);
}

int		main(int argc, char **argv)
{
	t_data	data;
	
	ft_setup(&data, argc, argv);
	mlx_hook(data.mlx_win, KEYPRESS, 1L<<0, ft_key_press, &data);
	mlx_hook(data.mlx_win, KEYRELEASE, 1L<<1, ft_key_release, &data);
	mlx_loop_hook(data.mlx, main_loop, &data);
	mlx_loop(data.mlx);
	return (0);
}
