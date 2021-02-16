/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarlos- <ocarlos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 16:09:30 by ocarlos-          #+#    #+#             */
/*   Updated: 2021/02/15 15:18:32 by ocarlos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// map matrix (TEMPORARY)
int map[MAP_ROWS][MAP_COLS] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
    {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

// int map[MAP_ROWS][MAP_COLS] = {
//     {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
//     {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
//     {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
//     {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
//     {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
//     {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
//     {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
//     {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
//     {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
//     {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
//     {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
//     {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
//     {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
// };

// initializes the main struct variables
int		ft_init_win(t_data *data)
{
	data->mlx = mlx_init();
	data->width = SCREENW;
	data->height = SCREENH;
	data->mlx_win = mlx_new_window(data->mlx, data->width, data->height, "A MAZE IN");
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
	data->player.walkSpeed = INIT_WALKSPD;
	data->player.turnSpeed = INIT_TURNSPD * (PI / 180);
}

// initializes the setup for the main loop
void	ft_setup(t_data *data, int argc, char **argv)
{
	//ft_maparray(argc, argv);  // reads the map into the main struct
	data->colorBuffer = (uint32_t*) malloc(sizeof(uint32_t) * (uint32_t)SCREENW * (uint32_t)SCREENH);
	ft_edit_colorbuffer(data, TEXTURE_INDEX);
	ft_init_win(data);
	ft_init_img(data);
	ft_init_player(data);
	ft_texture_gen(data, 0);
}

// finishes the program
void	ft_destroy(t_data *data)
{
	free(data->colorBuffer);
	free(data->textures[0]);
	mlx_destroy_window(data->mlx, data->mlx_win);
	exit(0);
}

// changes key status to pressed and destroys window if pressed ESC
int		ft_key_press(int keycode, t_data *data)
{
	if (keycode == ESC)
		ft_destroy(data);
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
void	ft_print_pixel(t_data *data, int x, int y, int color)
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
		ft_print_pixel(data, i_pos.x, i_pos.y, color);
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
int		ft_invalid_area(t_data *data, float x, float y)
{
	if (x < 0 || x > SCREENW || y < 0  || y > SCREENH)
		return (TRUE);
	int mapgridx = floor(x / TILE_SIZE);
	int mapgridy = floor(y / TILE_SIZE);
	return (map[mapgridy][mapgridx] != 0);
}

// normalize angle
float	ft_normalize_angle(float angle) 
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
	data->player.rotationAngle = ft_normalize_angle(data->player.rotationAngle);
	movestep = data->player.walkDirection * data->player.walkSpeed;
	playerCos = cos(data->player.rotationAngle) * movestep;
	playerSin = sin(data->player.rotationAngle) * movestep;
	newPlayerX = data->player.playerspr.pos.x + playerCos;
	newPlayerY = data->player.playerspr.pos.y + playerSin;
	if (!(ft_invalid_area(data, newPlayerX, newPlayerY)))
	{
		data->player.playerspr.pos.x = newPlayerX;
		data->player.playerspr.pos.y = newPlayerY;
	}
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
int		ft_render_ray(t_data *data)
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
	ft_edit_colorbuffer(data, 1);
	ft_render_map(data);
	ft_render_ray(data);
	ft_render_player(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->tile.img, 0, 0);
	return (TRUE);
}

// gets player moving direction and speed
int		ft_player_direction(t_data *data)
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
	return (TRUE);
}

// moves the image in the window
int		ft_update(t_data *data)
{
	ft_player_direction(data);
	ft_cast_all_rays(data);
	ft_move_player(data);
	ft_edit_colorbuffer(data, 0);
	ft_gen_3d_proj(data, 0);
	return (TRUE);
}

// loops until a wall is found - 0 for horizontal check and 1 for vertical check
int		ft_find_wall(t_data *data, t_rays *raytemp, t_coord toCheck, t_coord step, int is_vert)
{
	while (raytemp->nextTouch.x >= 0 && raytemp->nextTouch.x <= SCREENW && raytemp->nextTouch.y > 0 && raytemp->nextTouch.y <= SCREENH)
	{
		toCheck.x = raytemp->nextTouch.x;
		toCheck.y = raytemp->nextTouch.y;
		if (is_vert)
			toCheck.x += (raytemp->face_left ? -1 : 0);
		else
			toCheck.y += (raytemp->face_up ? -1 : 0);
		if (ft_invalid_area(data, toCheck.x, toCheck.y))
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
	intercept.y = floor(data->player.playerspr.pos.y / TILE_SIZE) * TILE_SIZE;
	intercept.y += raytemp->face_down ? TILE_SIZE : 0;
	intercept.x = data->player.playerspr.pos.x + (intercept.y - data->player.playerspr.pos.y) / tan(rayAngle);
	step.y = TILE_SIZE;
	step.y *= raytemp->face_up ? -1 : 1;
	step.x = TILE_SIZE / tan(rayAngle);
	step.x *= (raytemp->face_left && step.x > 0) ? -1 : 1;
	step.x *= (raytemp->face_right && step.x < 0) ? -1 : 1;
	raytemp->nextTouch.x = intercept.x;
	raytemp->nextTouch.y = intercept.y;
	ft_find_wall(data, raytemp, toCheck, step, 0);
	return (TRUE);
}

// calculates vertical ray intersection on the grid
int		ft_v_intersection(t_data *data, t_rays *raytemp, t_coord intercept, t_coord step, float rayAngle)
{
	t_coord	toCheck;

	raytemp->wallhit.x = 0;
	raytemp->wallhit.y = 0;
	intercept.x = floor(data->player.playerspr.pos.x / TILE_SIZE) * TILE_SIZE;
	intercept.x += raytemp->face_right ? TILE_SIZE : 0;
	intercept.y = data->player.playerspr.pos.y + (intercept.x - data->player.playerspr.pos.x) * tan(rayAngle);
	step.x = TILE_SIZE;
	step.x *= raytemp->face_left ? -1 : 1;
	step.y = TILE_SIZE * tan(rayAngle);
	step.y *= (raytemp->face_up && step.y > 0) ? -1 : 1;
	step.y *= (raytemp->face_down && step.y < 0) ? -1 : 1;
	raytemp->nextTouch.x = intercept.x;
	raytemp->nextTouch.y = intercept.y;
	ft_find_wall(data, raytemp, toCheck, step, 1);
	return (TRUE);
}

// initializes raytemp struct with basic values
int		ft_init_raytemp(t_rays *raytemp, float rayAngle)
{
	*raytemp = (t_rays) {0};  // fill the struct with zeroes
	raytemp->face_down = rayAngle > 0 && rayAngle < PI;
	raytemp->face_up = !(raytemp->face_down);
	raytemp->face_right = rayAngle < (0.5 * PI) || rayAngle > (1.5 * PI);
	raytemp->face_left = !(raytemp->face_right);
	return (TRUE);
}

// calculates the distance between two coordinates x and y
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

// copies the values from raytemp to actual ray struct array position
int		ft_fill_ray(t_data *data, t_rays *raytemp, int is_vert, int stripId)
{
	data->rays[stripId].distance = ft_distance(data, raytemp);
	data->rays[stripId].wallhit.x = raytemp->wallhit.x;
	data->rays[stripId].wallhit.y = raytemp->wallhit.y;
	data->rays[stripId].wallHitContent = raytemp->wallHitContent;
	data->rays[stripId].face_up = raytemp->face_up;
	data->rays[stripId].face_down = raytemp->face_down;
	data->rays[stripId].face_left = raytemp->face_left;
	data->rays[stripId].face_right = raytemp->face_right;
	data->rays[stripId].foundwall = raytemp->foundwall;
	data->rays[stripId].wallcontent = raytemp->wallcontent;
	if (is_vert)
		data->rays[stripId].verticalhit = TRUE;
	else
		data->rays[stripId].verticalhit = FALSE;
	return (TRUE);
}

// function responsible for casting each ray
int		ft_cast_ray(t_data *data, float rayAngle, int stripId)
{
	t_rays	raytemp_h;
	t_rays	raytemp_v;
	t_coord intercept;
	t_coord step;
	t_coord	distance;

	rayAngle = ft_normalize_angle(rayAngle);
	ft_init_raytemp(&raytemp_h, rayAngle);
	ft_init_raytemp(&raytemp_v, rayAngle);
	ft_h_intersection(data, &raytemp_h, intercept, step, rayAngle);
	ft_v_intersection(data, &raytemp_v, intercept, step, rayAngle);
	distance.x = raytemp_h.foundwall ? ft_distance(data, &raytemp_h) : __FLT_MAX__;
	distance.y = raytemp_v.foundwall ? ft_distance(data, &raytemp_v) : __FLT_MAX__;
	if (distance.y < distance.x)
		ft_fill_ray(data, &raytemp_v, 1, stripId);
	else
		ft_fill_ray(data, &raytemp_h, 0, stripId);
	data->rays[stripId].angle = rayAngle;
	return (TRUE);
}

// loop through all rays and fill the ray struct array
int		ft_cast_all_rays(t_data *data)
{
	float	rayAngle;
	int		stripId;

	stripId = 0;
	rayAngle = data->player.rotationAngle - (FOV / 2);
	while (stripId < NUM_RAYS)
	{
		ft_cast_ray(data, rayAngle, stripId);
		rayAngle += FOV / NUM_RAYS;
		rayAngle = ft_normalize_angle(rayAngle);
		stripId++;
	}
	return (TRUE);
}

// renders the color buffer and fills it with color in parameter
// print = 0 makes color buffer black
// print = 1 prints the color buffer on screen
int		ft_edit_colorbuffer(t_data *data, int print)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (x < SCREENW)
	{
		while (y < SCREENH)
		{
			if (print == 0)
				data->colorBuffer[(SCREENW * y) + x] = ft_crt_trgb(255, 0, 0, 0);
			if (print == 1)
				ft_print_pixel(data, x, y, data->colorBuffer[(SCREENW * y) + x]);
			y++;
		}
		y = 0;
		x++;
	}
	return (TRUE);
}

// projects the wall textures to each strip of each wall
int		ft_project_texture(t_data *data, t_3dproj *projection, int tex_ind)
{
	int		textOffsetY;
	int		textOffsetX;
	int		distanceFromTop;
	uint32_t test;

	if (data->rays[projection->i].verticalhit)
		textOffsetX = (int)data->rays[projection->i].wallhit.y % TILE_SIZE;
	else
		textOffsetX = (int)data->rays[projection->i].wallhit.x % TILE_SIZE;
	while (projection->y < projection->column_bottom)
	{
		distanceFromTop = (projection->y + (projection->strip_h / 2) - (SCREENH / 2));
		textOffsetY = distanceFromTop * ((float)TEXTURE_H / projection->strip_h);
		//data->colorBuffer[(SCREENW * projection->y) + projection->i] = data->textures[tex_ind][(SCREENW * textOffsetY) + textOffsetX];
		test = data->textures[tex_ind][(SCREENW * textOffsetY) + textOffsetX];
		data->colorBuffer[(SCREENW * projection->y) + projection->i] = test;
		projection->y++;
	}
	return (TRUE);
}

// generates the 3D projection using raycasting
void	ft_gen_3d_proj(t_data *data, int tex_ind)
{
	t_3dproj	projection;

	projection.i = 0;
	while (projection.i < NUM_RAYS)
	{
		projection.y = 0;
		projection.c_distance = data->rays[projection.i].distance * cos(data->rays[projection.i].angle - data->player.rotationAngle);
		projection.dist_proj_plane = (SCREENW / 2) / tan(FOV / 2);
		projection.proj_wall_h = (TILE_SIZE / projection.c_distance) * projection.dist_proj_plane;
		projection.strip_h = (int)projection.proj_wall_h;
		projection.column_top = (SCREENH / 2) - (floor(projection.proj_wall_h) / 2);
		projection.column_top = projection.column_top < 0 ? 0 : projection.column_top;
		projection.column_bottom = (SCREENH / 2) + (projection.proj_wall_h / 2);
		projection.column_bottom = projection.column_bottom > SCREENH ? SCREENH : projection.column_bottom;
		while (projection.y < projection.column_top)
			data->colorBuffer[(SCREENW * projection.y++) + projection.i] = ft_crt_trgb(255, 192, 192, 192);
		ft_project_texture(data, &projection, tex_ind);		
		while (projection.y < SCREENH)
			data->colorBuffer[(SCREENW * projection.y++) + projection.i] = ft_crt_trgb(255, 62, 64, 64);
		projection.i++;
	}
}
