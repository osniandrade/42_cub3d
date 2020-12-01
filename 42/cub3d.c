/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarlos- <ocarlos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 16:09:36 by ocarlos-          #+#    #+#             */
/*   Updated: 2020/12/01 15:39:31 by ocarlos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdlib.h>
#include <stdio.h>
#include "constants.c"
#include "functions.c"

// main loop - draws and moves the image
int		main_loop(t_data *data)
{
	int		sq_size = 60;
	
	ft_draw(data, sq_size);
	ft_update(data);
	//ft_move(data);
	return (TRUE);
}

int		main(void)
{
	t_data	data;

	ft_init(&data);
	mlx_hook(data.mlx_win, KEYPRESS, 1L<<0, ft_key_press, &data);
	mlx_hook(data.mlx_win, KEYRELEASE, 1L<<1, ft_key_release, &data);
	mlx_loop_hook(data.mlx, main_loop, &data);
	mlx_loop(data.mlx);
	return (0);
}