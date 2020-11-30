/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarlos- <ocarlos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 16:09:30 by ocarlos-          #+#    #+#             */
/*   Updated: 2020/11/30 18:14:22 by ocarlos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "constants.c"
#include "helper.c"

typedef struct	s_data
{
	void	*mlx;
	void	*mlx_win;
	int		width, height;
	int		x, y;
	int		up, down, left, right;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_data;

// changes key status to pressed and destroys window if pressed ESC
int		ft_key_press(int keycode, t_data *data)
{
	if (keycode == ESC)
	{
		mlx_destroy_window(data->mlx, data->mlx_win);
		exit(0);
	}
	if (keycode == LEFT)
		data->left = 1;
	if (keycode == RIGHT)
		data->right = 1;
	if (keycode == UP)
		data->up = 1;
	if (keycode == DOWN)
		data->down = 1;
	return (0);
}

// changes key status to not pressed
int		ft_key_release(int keycode, t_data *data)
{
	if (keycode == LEFT)
		data->left = 0;
	if (keycode == RIGHT)
		data->right = 0;
	if (keycode == UP)
		data->up = 0;
	if (keycode == DOWN)
		data->down = 0;
	return (0);
}

// draws a pixel to the image buffer
void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + ((y * data->line_length) + (x * (data->bits_per_pixel / 8)));
	*(unsigned int *)dst = color;
}

// draws a triangle to the window
int		ft_draw(t_data *data, int size)
{
	int		x = data->x;
	int		y = data->y;

	while (x < data->x + size)
	{
		while (y < data->y + size)
		{
			my_mlx_pixel_put(data, x, y, ft_crt_trgb(0,255,0,0));
			y++;
		}
		y = data-> y;
		x++;
	}
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);
	return (0);
}

// updates the image in the window
int		ft_update(t_data *data, int size)
{
	int		x = 0;
	int		y = 0;

	while (x < data->width)
	{
		while (y < data->height)
		{
			my_mlx_pixel_put(data, x, y, ft_crt_trgb(0,0,0,0));
			y++;
		}
		y = 0;
		x++;
	}
	ft_draw(data, size);
	return (0);
}

// moves the image in the window
int		ft_move(t_data *data)
{
	if (data->left == 1 && data->x > 0)
	{
		data->x -= 3;
		printf("x = %d, y = %d\n", data->x, data->y);
	}
	if (data->right == 1 && data->x < data->width)
	{
		data->x += 3;
		printf("x = %d, y = %d\n", data->x, data->y);
	}
	if (data->up == 1 && data->y > 0)
	{
		data->y -= 3;
		printf("x = %d, y = %d\n", data->x, data->y);
	}
	if (data->down == 1 && data->y < data->height)
	{
		data->y += 3;
		printf("x = %d, y = %d\n", data->x, data->y);
	}
	return (0);
}

int		ft_init(t_data *data)
{
	data->mlx = mlx_init();
	data->width = SCREENW;
	data->height = SCREENH;
	data->mlx_win = mlx_new_window(data->mlx, data->width, data->height, "RED SQUARE");
	data->img = mlx_new_image(data->mlx, SCREENW, SCREENH);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length, &data->endian);
	return (0);
}