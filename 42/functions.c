/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarlos- <ocarlos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 16:09:30 by ocarlos-          #+#    #+#             */
/*   Updated: 2021/01/20 16:59:06 by ocarlos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// map matrix (TEMPORARY)
// int map[MAP_ROWS][MAP_COLS] = {
//     {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
//     {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
//     {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
//     {1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1},
//     {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
//     {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
//     {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
//     {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
//     {1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1},
//     {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
//     {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
//     {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1},
//     {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
// };

int map[MAP_ROWS][MAP_COLS] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

// initializes the main struct variables
int		ft_init_win(t_data *data)
{
	data->mlx = mlx_init();
	data->width = SCREENW * MAP_SCALE;
	data->height = SCREENH * MAP_SCALE;
	data->mlx_win = mlx_new_window(data->mlx, data->width, data->height, "RED SQUARE");
	data->maptable = &map;
	return (TRUE);
}

// initializes a new image's struct
void	ft_init_img(t_data *data)
{
	t_img	imagem;

	imagem.img = mlx_new_image(data->mlx, SCREENW, SCREENH);
	imagem.addr = mlx_get_data_addr(imagem.img, &imagem.bits_per_pixel, 
									&imagem.line_length, &imagem.endian);
	imagem.pos.x = 0;
	imagem.pos.y = 0;
	imagem.s = 50;
	data->tile = imagem;
}

// initializes player data
void	ft_init_player(t_data *data)
{
	data->player.playerspr.pos.x = (SCREENW / 2);
	data->player.playerspr.pos.y = (SCREENH / 2);
	data->player.turnDirection = 0;
	data->player.walkDirection = 0;
	data->player.rotationAngle = PI / 2;
	data->player.walkSpeed = 6 * GAMESPEED;
	data->player.turnSpeed = (4 * GAMESPEED) * (PI / 180);
}

// initializes the setup for the main loop
void	ft_setup(t_data *data, int argc, char **argv)
{
	//ft_maparray(argc, argv);  // reads the map into the main struct
	ft_init_win(data);
	ft_init_img(data);
	ft_init_player(data);
}

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
	if (data->tile.pos.y <= data->height && data->tile.pos.x <= data->width)
	{
		dst = data->tile.addr + ((y * data->tile.line_length) + (x * (data->tile.bits_per_pixel / 8)));
		*(unsigned int *)dst = color;
	}
}

// draws a line from i_pos to f_pos in color (Bresenham's algorithm)
int		ft_draw_line(t_data *data, t_coord i_pos, t_coord f_pos, int color)
{
	int dx = abs(f_pos.x - i_pos.x);
	int sx = i_pos.x < f_pos.x ? 1 : -1;
	int dy = abs(f_pos.y - i_pos.y);
	int sy = i_pos.y < f_pos.y ? 1 : -1;
	int err = (dx > dy ? dx : -dy) / 2;
	int e2;

	while(!(i_pos.x == f_pos.x && i_pos.y == f_pos.y))
	{
		my_mlx_pixel_put(data, i_pos.x, i_pos.y, color);
		e2 = err;
		if (e2 > -dx)
		{
			err -= dy;
			i_pos.x += sx;
		}
		if (e2 < dy)
		{
			err += dx;
			i_pos.y += sy;
		}
	}
	return (TRUE);
}

// draws a rectangle with defined heigth, width and color
int		ft_draw_rect(t_data *data, int h, int w, int color)
{
	t_coord	i_pos, f_pos;

	i_pos.x = data->tile.pos.x;
	i_pos.y = data->tile.pos.y;
	f_pos.x = data->tile.pos.x + w;
	f_pos.y = data->tile.pos.y;
	while (i_pos.y <= data->tile.pos.y + h)
	{
		ft_draw_line(data, i_pos, f_pos, color);
		i_pos.y++;
		f_pos.y++;
	}
	return (TRUE);
}

// draws the player on minimap
int		ft_draw_player(t_data *data, int color)
{
	t_coord i_pos, f_pos;

	i_pos.x = MAP_SCALE * data->player.playerspr.pos.x;
	i_pos.y = MAP_SCALE * data->player.playerspr.pos.y;
	f_pos.x = MAP_SCALE * data->player.playerspr.pos.x + cos(data->player.rotationAngle) * PLAYERSIZE;
	f_pos.y = MAP_SCALE * data->player.playerspr.pos.y + sin(data->player.rotationAngle) * PLAYERSIZE;

	ft_draw_line(data, i_pos, f_pos, color);

	return (TRUE);
}

// checks if image is in drawable area, uses "step" as increment
int		ft_invalidarea(t_data *data, float x, float y)
{
	if (x < 0 || x > SCREENW || y < 0  || y > SCREENH)
		return (TRUE);
	int mapgridx = floor(x / TILE_SIZE);
	int mapgridy = floor(y / TILE_SIZE);
	return (map[mapgridy][mapgridx] != 0);
}

// updates player positions and directions
int		ft_move_player(t_data *data)
{
	float	movestep;
	float	newPlayerX;
	float	newPlayerY;

	data->player.rotationAngle += data->player.turnDirection * data->player.turnSpeed;
	if (data->player.rotationAngle >= 2 * PI)
		data->player.rotationAngle = 0;
	if (data->player.rotationAngle < 0)
		data->player.rotationAngle = 2 * PI;
	movestep = data->player.walkDirection * data->player.walkSpeed;
	newPlayerX = data->player.playerspr.pos.x + cos(data->player.rotationAngle) * movestep;
	newPlayerY = data->player.playerspr.pos.y + sin(data->player.rotationAngle) * movestep;
	if (!(ft_invalidarea(data, newPlayerX, newPlayerY)))
	{
		data->player.playerspr.pos.x = round(newPlayerX);
		data->player.playerspr.pos.y = round(newPlayerY);
	}
}

// erases the image in the window drawing a black rectangle on top of each tile
int		ft_erase(t_data *data)
{
	ft_draw_rect(data, data->tile.s, data->tile.s, ft_crt_trgb(0,0,0,0));
	return (TRUE);
}

// renders map
int		ft_render_map(t_data *data)
{
	int tileColor;
	int i = 0;
	int j = 0;

	while (i < MAP_ROWS)
	{
		while (j < MAP_COLS)
		{
			data->tile.pos.x = (j * TILE_SIZE) * MAP_SCALE;
			data->tile.pos.y = (i * TILE_SIZE) * MAP_SCALE;
			tileColor = (map[i][j] != 0) ? ft_crt_trgb(0,255,255,255) : 0;
			ft_draw_rect(data, 
					  TILE_SIZE * MAP_SCALE, 
					  TILE_SIZE * MAP_SCALE, 
					  tileColor);
			j++;
		}
		j = 0;
		i++;
	}
}

// renders player sprite on screen
int		ft_render_player(t_data *data)
{
	ft_draw_player(data, ft_crt_trgb(0, 255, 0, 255));
	data->player.walkDirection = 0;
	data->player.turnDirection = 0;
	return (TRUE);
}

// draws elements in the window
int		ft_draw(t_data *data)
{
	ft_render_map(data);
	ft_render_player(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->tile.img, 0, 0);
	return (TRUE);
}

// updates object position
int		ft_update(t_data *data)
{
	int cnt = 0;

	while(cnt++ < 2 * FPS); // stupid fps control method
	if (!(ft_invalidarea(data, data->tile.pos.x, data->tile.pos.y)))
	{
		data->tile.pos.x += 2;
		data->tile.pos.y += 2;
		return (TRUE);
	}
	else
		return (FALSE);
}

// moves the image in the window
int		ft_move(t_data *data)
{
	if (data->left == TRUE)
		data->player.turnDirection = -MOVESPEED;
	if (data->right == TRUE)
		data->player.turnDirection = +MOVESPEED;
	if (data->up == TRUE)
		data->player.walkDirection = +MOVESPEED;
	if (data->down == TRUE)
		data->player.walkDirection = -MOVESPEED;
	if (data->up == FALSE && data->down == FALSE)
		data->player.walkDirection = 0;
	if (data->left == FALSE && data->right == FALSE)
		data->player.turnDirection = 0;

	// test purposes only
	printf("x = %d, y = %d\n", data->player.playerspr.pos.x, data->player.playerspr.pos.y);
	printf("angle = %f\n", data->player.rotationAngle);
	ft_test_collision(data);
	
	ft_move_player(data);	

	return (TRUE);
}
