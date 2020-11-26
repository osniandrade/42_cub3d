/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarlos- <ocarlos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 16:09:36 by ocarlos-          #+#    #+#             */
/*   Updated: 2020/11/26 10:08:33 by ocarlos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "functions.c"
#include "constants.c"
#include "helper.c"

int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	int		drwx;
	int		drwy;
	t_data	img;

	drwx = 5;
	drwy = 5;
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, SCREENW, SCREENH, "RED SQUARE!");
	img.img = mlx_new_image(mlx, SCREENW, SCREENH);
	img.color = ft_crt_trgb(0, 255, 0, 0);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
								 &img.line_length, &img.endian);
	while (drwx < SCREENH - 60 && drwy < SCREENW - 60)
		ft_drawbasicshape(&img, drwx++, drwy++, 1, 60);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}