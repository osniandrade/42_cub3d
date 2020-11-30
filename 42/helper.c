/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarlos- <ocarlos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 09:29:52 by ocarlos-          #+#    #+#             */
/*   Updated: 2020/11/30 10:40:03 by ocarlos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "constants.c"
#include <stdio.h>

typedef struct	s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int 	endian; // if machine is little endian it will be 0, otherwise, 1
	int 	color;  // image color
	int		px;     // image x position
	int		py;     // image y position
} 			t_data;

typedef struct	s_vars {
	void	*mlx;  // connection do display
	void	*win;  // window
	int		wtdx;  // where to draw x
	int		wtdy;  // where to draw y
}			t_vars;

// creates a buffer to renderize before writing a image to screen
// rendering offset included to garantee the draw is within the window limits
void	ft_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + ((y * data->line_length) + (x * (data->bits_per_pixel / 8)));
	*(unsigned int *)dst = color;
}

// draw basic shapes
// 1 = square
int		ft_drawbasicshape(t_data *data, int x, int y, int shape, int size)
{
	int newx;
	int newy;

	newx = x;
	newy = y;
	if (shape = 1)
	{
		while (newx++ < x + size)
		{
			while (newy++ < y + size)
				ft_mlx_pixel_put(data, newx, newy, data->color);
			newy = y;
		}
		return (TRUE);
	}
	return (FALSE);
}

// key capture using hook
int		ft_key_hook(int keycode, t_vars *vars)
{
	printf("Hello from key_hook!\n");
}

// close the window when esc key is pressed
int		ft_close_win(int keycode, t_vars *vars)
{
	if (keycode == ESCAPEKEY)
		mlx_destroy_window(vars->mlx, vars->win);
}

int		ft_draw_frame(t_vars *vars)
{
	t_data	img;

	img.px = vars->wtdx++;
	img.py = vars->wtdy++;
	img.endian = ft_bg_endian();
	img.img = mlx_new_image(vars->mlx, SCREENW, SCREENH);
	img.color = ft_crt_trgb(0,255,0,0);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
								  &img.line_length, &img.endian);
	if (vars->wtdx + 60 == SCREENW || vars->wtdy + 60 == SCREENH)
		return (FALSE);
	else
	{
		ft_drawbasicshape(&img, img.px, img.py, 1, 60);
		mlx_put_image_to_window(vars->mlx, vars->win, img.img, 0, 0);
		return (TRUE);
	}
}