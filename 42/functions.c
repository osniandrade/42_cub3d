/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarlos- <ocarlos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 16:09:30 by ocarlos-          #+#    #+#             */
/*   Updated: 2020/12/02 09:17:49 by ocarlos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>  // REMOVE LATER
#include "constants.c"
#include "helper.c"

typedef struct	s_data
{
	void	*mlx;
	void	*mlx_win;
	int		width, height;
	int		x, y, s;
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
		data->left = TRUE;
	if (keycode == RIGHT)
		data->right = TRUE;
	if (keycode == UP)
		data->up = TRUE;
	if (keycode == DOWN)
		data->down = TRUE;
	return (TRUE);
}

// changes key status to not pressed
int		ft_key_release(int keycode, t_data *data)
{
	if (keycode == LEFT)
		data->left = FALSE;
	if (keycode == RIGHT)
		data->right = FALSE;
	if (keycode == UP)
		data->up = FALSE;
	if (keycode == DOWN)
		data->down = FALSE;
	return (TRUE);
}

// draws a pixel to the image buffer
void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + ((y * data->line_length) + (x * (data->bits_per_pixel / 8)));
	*(unsigned int *)dst = color;
}

// draws a rectangle with defined heigth, width and color
int		ft_d_rect(t_data *data, int h, int w, int color)
{
	int		x = data->x;
	int 	y = data->y;

	while (x < w + data->x)
	{
		while (y < h + data->y)
			my_mlx_pixel_put(data, x, y++, color);
		y = data->y;
		x++;
	}
	return (TRUE);
}

// updates the image in the window
int		ft_erase(t_data *data)
{
	ft_d_rect(data, data->s, data->s, ft_crt_trgb(0,0,0,0));
	return (TRUE);
}

// draws a square to the window
int		ft_draw(t_data *data)
{
	ft_d_rect(data, data->s, data->s, ft_crt_trgb(0,255,0,0));
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);
	return (TRUE);
}

// checks if image is in drawable area, uses "step" as 
int		ft_validarea(t_data *data, int step)
{
	if ((data->x + step <= data->width - data->s) && 
		(data->y + step <= data->height - data->s))
		return (TRUE);
	else
		return (FALSE);
}

// updates object position
int		ft_update(t_data *data)
{
	int cnt = 0;

	while(cnt++ < 2 * FPS); // stupid fps control method
	if (ft_validarea(data, 2))
	{
		data->x += 2;
		data->y += 2;
		return (TRUE);
	}
	else
		return (FALSE);
}

// moves the image in the window
int		ft_move(t_data *data)
{
	if (data->left == TRUE && data->x > 0)
	{
		if (ft_validarea(data, -MOVESPEED))
			data->x -= MOVESPEED;
		printf("x = %d, y = %d\n", data->x, data->y);
	}
	if (data->right == TRUE && data->x < data->width)
	{
		if (ft_validarea(data, MOVESPEED))
			data->x += MOVESPEED;
		printf("x = %d, y = %d\n", data->x, data->y);
	}
	if (data->up == TRUE && data->y > 0)
	{
		if (ft_validarea(data, -MOVESPEED))
			data->y -= MOVESPEED;
		printf("x = %d, y = %d\n", data->x, data->y);
	}
	if (data->down == TRUE && data->y < data->height)
	{
		if (ft_validarea(data, MOVESPEED))
			data->y += MOVESPEED;
		printf("x = %d, y = %d\n", data->x, data->y);
	}
	return (TRUE);
}

// initializes the main struct variables
int		ft_init(t_data *data)
{
	data->mlx = mlx_init();
	data->width = SCREENW;
	data->height = SCREENH;
	data->mlx_win = mlx_new_window(data->mlx, data->width, data->height, "RED SQUARE");
	data->img = mlx_new_image(data->mlx, SCREENW, SCREENH);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length, &data->endian);
	data->x = STARTX;
	data->y = STARTY;
	data->s = 50;
	return (TRUE);
}