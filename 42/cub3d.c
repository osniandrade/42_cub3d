/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarlos- <ocarlos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 16:09:36 by ocarlos-          #+#    #+#             */
/*   Updated: 2020/11/30 11:12:56 by ocarlos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "functions.c"
#include "constants.c"
#include "helper.c"

int	main(void)
{
	int		drwx;
	int		drwy;
	t_vars	vars;

	// TODO
	// stop drawing after trying to do it out of window
	vars.wtdx = 5;
	vars.wtdy = 5;
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, SCREENW, SCREENH, "RED SQUARE!");
	mlx_hook(vars.win, 2, 1L<<0, ft_close_win, &vars);
	ft_draw_frame(&vars);
	mlx_loop_hook(vars.mlx, ft_draw_frame, &vars);
	mlx_loop(vars.mlx);
}