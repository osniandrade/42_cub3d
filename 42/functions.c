/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarlos- <ocarlos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 16:09:30 by ocarlos-          #+#    #+#             */
/*   Updated: 2021/02/04 20:53:23 by ocarlos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//map matrix (TEMPORARY)
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
	data->player.rotationAngle = 0; //PI / 2;
	data->player.walkSpeed = INIT_WALKSPD;
	data->player.turnSpeed = INIT_TURNSPD * (PI / 180);
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

// draws a rectangle with defined height, width and color
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

	i_pos.x = round(MAP_SCALE * data->player.playerspr.pos.x);
	i_pos.y = round(MAP_SCALE * data->player.playerspr.pos.y);
	f_pos.x = round(MAP_SCALE * data->player.playerspr.pos.x + cos(data->player.rotationAngle) * PLAYERSIZE);
	f_pos.y = round(MAP_SCALE * data->player.playerspr.pos.y + sin(data->player.rotationAngle) * PLAYERSIZE);

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

// normalize angle
float	ft_normalizeangle(float angle) 
{
	angle = remainder(angle, PI * 2);
	if (angle < 0) 
	{
		angle = (2 * PI) + angle;
	}
	return (angle);
}

// updates player positions and directions
int		ft_move_player(t_data *data)
{
	float	movestep;
	float	newPlayerX;
	float	newPlayerY;
	float	playerCos;
	float	playerSin;

	data->player.rotationAngle += data->player.turnDirection * data->player.turnSpeed;
	data->player.rotationAngle = ft_normalizeangle(data->player.rotationAngle);
	movestep = data->player.walkDirection * data->player.walkSpeed;
	playerCos = cos(data->player.rotationAngle) * movestep;
	playerSin = sin(data->player.rotationAngle) * movestep;
	newPlayerX = data->player.playerspr.pos.x + playerCos;
	newPlayerY = data->player.playerspr.pos.y + playerSin;
	if (!(ft_invalidarea(data, newPlayerX, newPlayerY)))
	{
		data->player.playerspr.pos.x = newPlayerX;
		data->player.playerspr.pos.y = newPlayerY;
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

// renders all rays from rays array on screen
int		ft_renderray(t_data *data)
{
	int		ray;
	int		color;
	t_coord i_pos;
	t_coord f_pos;

	ray = 0;
	color = ft_crt_trgb(255, 0, 0, 255);
	while (ray < NUM_RAYS)
	{
		i_pos.x = round(MAP_SCALE * data->player.playerspr.pos.x);
		i_pos.y = round(MAP_SCALE * data->player.playerspr.pos.y);
		f_pos.x = round(MAP_SCALE * data->rays[ray].wallhit.x);
		f_pos.y = round(MAP_SCALE * data->rays[ray].wallhit.y);
		ft_draw_line(data, i_pos, f_pos, color);
		ray++;
	}
}

// draws elements in the window
int		ft_draw(t_data *data)
{
	ft_render_map(data);
	ft_render_player(data);
	ft_renderray(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->tile.img, 0, 0);
	return (TRUE);
}

// updates object position
int		ft_update(t_data *data)
{
	// int cnt = 0;

	// while(cnt++ < 2 * FPS); // stupid fps control method
	// if (!(ft_invalidarea(data, data->tile.pos.x, data->tile.pos.y)))
	// {
	// 	data->tile.pos.x += 2;
	// 	data->tile.pos.y += 2;
	// 	return (TRUE);
	// }
	// else
	// 	return (FALSE);
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
	printf("x = %f, y = %f\n", data->player.playerspr.pos.x, data->player.playerspr.pos.y);
	printf("angle = %f\n", data->player.rotationAngle);
	//ft_test_collision(data);
	
	ft_move_player(data);

	return (TRUE);
}

// loops until a wall is found - 0 for horizontal check and 1 for vertical check
int		ft_findwall(t_data *data, t_rays *raytemp, t_coord toCheck, t_coord step, int is_vert)
{
	while (raytemp->nextTouch.x >= 0 && raytemp->nextTouch.x <= SCREENW && raytemp->nextTouch.y > 0 && raytemp->nextTouch.y <= SCREENH)
	{
		toCheck.x = raytemp->nextTouch.x;
		toCheck.y = raytemp->nextTouch.y;
		if (is_vert)
			toCheck.x += (raytemp->rayleft ? -1 : 0);
		else
			toCheck.y += (raytemp->rayup ? -1 : 0);
		if (ft_invalidarea(data, toCheck.x, toCheck.y))
		{
			raytemp->wallhit.x = raytemp->nextTouch.x;
			raytemp->wallhit.y = raytemp->nextTouch.y;
			raytemp->wallcontent = map[(int)floor(toCheck.y / TILE_SIZE)][(int)floor(toCheck.x / TILE_SIZE)];
			raytemp->foundwall = TRUE;
			break;
		}
		else
		{
			raytemp->nextTouch.x += step.x;
			raytemp->nextTouch.y += step.y;
		}
	}
}

// calculates horizontal ray intersection on the grid
int		ft_h_intersection(t_data *data, t_rays *raytemp, t_coord intercept, t_coord step, float rayAngle)
{
	t_coord	toCheck;

	raytemp->wallhit.x = 0;
	raytemp->wallhit.y = 0;

	// find y of closest horz grid intersection
	intercept.y = floor(data->player.playerspr.pos.y / TILE_SIZE) * TILE_SIZE;
	intercept.y += raytemp->raydown ? TILE_SIZE : 0;

	// find x of closest horz grid intersection
	intercept.x = data->player.playerspr.pos.x + (intercept.y - data->player.playerspr.pos.y) / tan(rayAngle);

	// calculate increment xstep and ystep
	step.y = TILE_SIZE;
	step.y *= raytemp->rayup ? -1 : 1;

	step.x = TILE_SIZE / tan(rayAngle);
	step.x *= (raytemp->rayleft && step.x > 0) ? -1 : 1;
	step.x *= (raytemp->rayright && step.x < 0) ? -1 : 1;

	raytemp->nextTouch.x = intercept.x;
	raytemp->nextTouch.y = intercept.y;

	// increment xstep and ystep until we find a wall
	ft_findwall(data, raytemp, toCheck, step, 0);
	
	return (TRUE);
}

// calculates vertical ray intersection on the grid
int		ft_v_intersection(t_data *data, t_rays *raytemp, t_coord intercept, t_coord step, float rayAngle)
{
	t_coord	toCheck;

	raytemp->wallhit.x = 0;
	raytemp->wallhit.y = 0;

	// find y of closest vert grid intersection
	intercept.x = floor(data->player.playerspr.pos.x / TILE_SIZE) * TILE_SIZE;
	intercept.x += raytemp->rayright ? TILE_SIZE : 0;

	// find x of closest vert grid intersection
	intercept.y = data->player.playerspr.pos.y + (intercept.x - data->player.playerspr.pos.x) * tan(rayAngle);

	// calculate increment xstep and ystep
	step.x = TILE_SIZE;
	step.x *= raytemp->rayleft ? -1 : 1;

	step.y = TILE_SIZE * tan(rayAngle);
	step.y *= (raytemp->rayup && step.y > 0) ? -1 : 1;
	step.y *= (raytemp->raydown && step.y < 0) ? -1 : 1;

	raytemp->nextTouch.x = intercept.x;
	raytemp->nextTouch.y = intercept.y;

	// increment xstep and ystep until we find a wall
	ft_findwall(data, raytemp, toCheck, step, 1);
	
	return (TRUE);
}

// initializes raytemp struct with basic values
int		ft_init_raytemp(t_rays *raytemp, float rayAngle)
{
	raytemp->rayup = rayAngle < 0 && rayAngle >= PI;
	//raytemp->raydown = !(raytemp->rayup);
	raytemp->raydown = rayAngle >= 0 && rayAngle < PI;
	raytemp->rayright = rayAngle <= 0.5 * PI && rayAngle > 1.5 * PI;
	//raytemp->rayleft = !(raytemp->rayright);
	raytemp->rayleft = rayAngle > 0.5 * PI && rayAngle <= 1.5 * PI;
	return (TRUE);
}

float	ft_distance(t_data *data, t_rays *raytemp)
{
	float coordx;
	float coordy;

	coordx = raytemp->wallhit.x - data->player.playerspr.pos.x;
	coordx *= coordx;
	coordy = raytemp->wallhit.y - data->player.playerspr.pos.y;
	coordy *= coordy;
	
	return sqrt(coordx + coordy);
}

int		ft_fillray(t_data *data, t_rays *raytemp, int is_vert, int stripId)
{
	data->rays[stripId].distance = 30; //raytemp->distance;
	data->rays[stripId].wallhit.x = raytemp->wallhit.x;
	data->rays[stripId].wallhit.y = raytemp->wallhit.y;
	data->rays[stripId].wallHitContent = raytemp->wallHitContent;
	data->rays[stripId].rayup = raytemp->rayup;
	data->rays[stripId].raydown = raytemp->raydown;
	data->rays[stripId].rayleft = raytemp->rayleft;
	data->rays[stripId].rayright = raytemp->rayright;
	data->rays[stripId].foundwall = raytemp->foundwall;
	data->rays[stripId].wallcontent = raytemp->wallcontent;
	if (is_vert)
		data->rays[stripId].verticalhit = TRUE;
	else
		data->rays[stripId].verticalhit = FALSE;
	return (TRUE);
}

// function responsible for casting each ray
int		ft_raycast(t_data *data, float rayAngle, int stripId)
{
	t_rays	raytemp_h;
	t_rays	raytemp_v;
	t_coord intercept;
	t_coord step;
	t_coord	distance;

	rayAngle = ft_normalizeangle(rayAngle);

	ft_init_raytemp(&raytemp_h, rayAngle);
	ft_init_raytemp(&raytemp_v, rayAngle);

	ft_h_intersection(data, &raytemp_h, intercept, step, rayAngle);
	ft_v_intersection(data, &raytemp_v, intercept, step, rayAngle);
	
	distance.x = raytemp_h.foundwall ? ft_distance(data, &raytemp_h) : __INT_MAX__;
	distance.y = raytemp_v.foundwall ? ft_distance(data, &raytemp_v) : __INT_MAX__;

	if (distance.y < distance.x)
		ft_fillray(data, &raytemp_v, 1, stripId);
	else
		ft_fillray(data, &raytemp_h, 0, stripId);
	data->rays[stripId].angle = rayAngle;
	return (TRUE);
}

int		ft_cast_all_rays(t_data *data)
{
	float	rayAngle;
	int		stripId;

	stripId = 0;
	rayAngle = data->player.rotationAngle - (FOV / 2);
	while (stripId < NUM_RAYS)
	{
		ft_raycast(data, rayAngle, stripId);
		rayAngle += FOV / NUM_RAYS;
		rayAngle = ft_normalizeangle(rayAngle);
		stripId++;
	}
	return (TRUE);
}
