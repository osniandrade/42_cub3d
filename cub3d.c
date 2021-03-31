/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarlos- <ocarlos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 16:09:36 by ocarlos-          #+#    #+#             */
/*   Updated: 2021/03/31 10:54:26 by ocarlos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		main_loop(t_data *d)
{
	ft_update(d);
	ft_draw(d);
	return (TRUE);
}

int		main(int argc, char **argv)
{
	t_data	d;
	
	d = (t_data) {0};
	ft_load_cub_file(&d, argc, argv);
	ft_setup(&d);
	mlx_hook (d.mlx_win, KEYRELEASE, 1L<<1, ft_key_release, &d);
	mlx_hook (d.mlx_win, KEYPRESS, 1L<<0, ft_key_press, &d);
	mlx_hook (d.mlx_win, MOUSECLICK, 1L<<17, ft_mouseclose, &d);
	mlx_loop_hook (d.mlx, main_loop, &d);
	mlx_loop (d.mlx);
	return (0);
}
