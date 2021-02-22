/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarlos- <ocarlos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 16:09:30 by ocarlos-          #+#    #+#             */
/*   Updated: 2021/02/22 11:34:23 by ocarlos-         ###   ########.fr       */
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

// textures paths (TEMPORARY)
static char* texpath[TEXTURE_COUNT] = {
	"./img/stonewall.xpm",
	"./img/moldystonewall.xpm",
	"./img/labwall.xpm",
	"./img/bunkerwall.xpm"
};

// sprites paths (TEMPORARY)
static char* sprpath[SPRITE_COUNT] = {
	"./img/guard.xpm"
};

// initializes the main struct variables
int		ft_init_win(t_data *data)
{
	data->mlx = mlx_init();
	data->size.w = SCREENW;
	data->size.h = SCREENH;
	data->mlx_win = mlx_new_window(data->mlx, data->size.w, data->size.h, "A MAZE IN");
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

// loads sprite paths from file to struct
void	ft_load_file_paths(char **dstpath, char **srcpath, int i)
{
	while (--i >= 0)
	{
		dstpath[i] = srcpath[i];
	}
}

// loads xpm texture file into code
void	ft_load_xpm_texture(t_data *data)
{
	int i = 0;

	while (i < TEXTURE_COUNT)
	{
		data->texture[i].instance.img = mlx_xpm_file_to_image(
			data->mlx, 
			data->texturepaths[i], 
			&data->texture[i].size.w, 
			&data->texture[i].size.h
		);
		data->texture[i].instance.addr = mlx_get_data_addr(
			data->texture[i].instance.img, 
			&(data->texture[i].instance.bits_per_pixel), 
			&(data->texture[i].instance.line_length), 
			&(data->texture[i].instance.endian)
		);
		data->texture[i].buffer = (uint32_t *) data->texture[i].instance.addr;
		i++;
	}
}

// loads sprite textures from array to a new image
void	ft_load_xpm_sprite(t_data *data)
{
	int i = 0;

	while (i < SPRITE_COUNT)
	{
		data->sprite[i].texture.instance.img = mlx_xpm_file_to_image(
			data->mlx,
			data->spritepaths[i],
			&data->sprite[i].texture.size.w,
			&data->sprite[i].texture.size.h
		);
		data->sprite[i].texture.instance.addr = mlx_get_data_addr(
			data->sprite[i].texture.instance.img,
			&(data->sprite[i].texture.instance.bits_per_pixel),
			&(data->sprite[i].texture.instance.line_length),
			&(data->sprite[i].texture.instance.endian)
		);
		data->sprite[i].texture.buffer = (uint32_t *) data->sprite[i].texture.instance.addr;
		i++;
	}
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

// loads map into data structure
int		ft_loadmap(t_data *data)
{
	data->maptable = &map;
	return (TRUE);
}

// initializes the setup for the main loop
void	ft_setup(t_data *data, int argc, char **argv)
{
	//ft_maparray(argc, argv);  // reads the map into the main struct
	data->colorBuffer = (uint32_t*) malloc(sizeof(uint32_t) * (uint32_t)SCREENW * (uint32_t)SCREENH);
	ft_edit_colorbuffer(data, 0);
	ft_init_win(data);
	ft_init_img(data);
	ft_load_file_paths(data->texturepaths, texpath, TEXTURE_COUNT);
	ft_load_file_paths(data->spritepaths, sprpath, SPRITE_COUNT);
	ft_load_xpm_texture(data);
	ft_load_xpm_sprite(data);
	ft_loadmap(data);
	ft_init_player(data);
}

// frees texture memory allocations
void	ft_destroy_images(t_data *data)
{
	int i = 0;

	mlx_destroy_image(data->mlx, data->tile.img);
	while (i < TEXTURE_COUNT)
	{
		mlx_destroy_image(data->mlx, data->texture[i].instance.img);
		i++;
	}
	i = 0;
	while (i < SPRITE_COUNT)
	{
		mlx_destroy_image(data->mlx, data->sprite[i].texture.instance.img);
		i++;
	}
}

// finishes the program
void	ft_destroy(t_data *data)
{
	free(data->colorBuffer);
	ft_destroy_images(data);
	mlx_destroy_window(data->mlx, data->mlx_win);
	exit(0);
}

// changes key status to pressed and destroys window if pressed ESC
int		ft_key_press(int keycode, t_data *data)
{
	if (keycode == ESC)
		ft_destroy(data);
	if (keycode == LEFT)
		data->dir.l = TRUE;
	if (keycode == RIGHT)
		data->dir.r = TRUE;
	if (keycode == UP)
		data->dir.u = TRUE;
	if (keycode == DOWN)
		data->dir.d = TRUE;
	return (TRUE);
}

// changes key status to not pressed
int		ft_key_release(int keycode, t_data *data)
{
	if (keycode == LEFT)
		data->dir.l = FALSE;
	if (keycode == RIGHT)
		data->dir.r = FALSE;
	if (keycode == UP)
		data->dir.u = FALSE;
	if (keycode == DOWN)
		data->dir.d = FALSE;
	return (TRUE);
}

// draws a pixel to the image buffer
void	ft_print_pixel(t_data *data, int x, int y, int color)
{
	char	*dst;
	if (data->tile.pos.y <= data->size.h && data->tile.pos.x <= data->size.w)
	{
		dst = data->tile.addr + ((y * data->tile.line_length) + (x * (data->tile.bits_per_pixel / 8)));
		*(unsigned int *)dst = color;
	}
}

// draws a line from i_pos to f_pos in color (Bresenham's algorithm)
int		ft_draw_line(t_data *data, t_coord i_pos, t_coord f_pos, int color)
{
	int dx = abs((int)f_pos.x - (int)i_pos.x);
	int sx = i_pos.x < f_pos.x ? 1 : -1;
	int dy = abs((int)f_pos.y - (int)i_pos.y);
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
	if (map[mapgridy][mapgridx] == 0)
		return (FALSE);
	else
		return (TRUE);
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
	return (TRUE);
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
	return (TRUE);
}

// draws elements in the window
int		ft_draw(t_data *data)
{
	ft_edit_colorbuffer(data, 1);
	//ft_render_map(data);
	//ft_render_ray(data);
	//ft_render_player(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->tile.img, 0, 0);
	return (TRUE);
}

// gets player moving direction and speed
int		ft_player_direction(t_data *data)
{
	if (data->dir.l == TRUE)
		data->player.turnDirection = -MOVESPEED;
	if (data->dir.r == TRUE)
		data->player.turnDirection = +MOVESPEED;
	if (data->dir.u == TRUE)
		data->player.walkDirection = +MOVESPEED;
	if (data->dir.d == TRUE)
		data->player.walkDirection = -MOVESPEED;
	if (data->dir.u == FALSE && data->dir.d == FALSE)
		data->player.walkDirection = 0;
	if (data->dir.l == FALSE && data->dir.r == FALSE)
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
	ft_gen_3d_proj(data);
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
			toCheck.x += (raytemp->face.l ? -1 : 0);
		else
			toCheck.y += (raytemp->face.u ? -1 : 0);
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
	return (TRUE);
}

// calculates horizontal ray intersection on the grid
int		ft_h_intersection(t_data *data, t_rays *raytemp, t_coord intercept, t_coord step, float rayAngle)
{
	t_coord	toCheck;

	raytemp->wallhit.x = 0;
	raytemp->wallhit.y = 0;
	intercept.y = floor(data->player.playerspr.pos.y / TILE_SIZE) * TILE_SIZE;
	intercept.y += raytemp->face.d ? TILE_SIZE : 0;
	intercept.x = data->player.playerspr.pos.x + (intercept.y - data->player.playerspr.pos.y) / tan(rayAngle);
	step.y = TILE_SIZE;
	step.y *= raytemp->face.u ? -1 : 1;
	step.x = TILE_SIZE / tan(rayAngle);
	step.x *= (raytemp->face.l && step.x > 0) ? -1 : 1;
	step.x *= (raytemp->face.r && step.x < 0) ? -1 : 1;
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
	intercept.x += raytemp->face.r ? TILE_SIZE : 0;
	intercept.y = data->player.playerspr.pos.y + (intercept.x - data->player.playerspr.pos.x) * tan(rayAngle);
	step.x = TILE_SIZE;
	step.x *= raytemp->face.l ? -1 : 1;
	step.y = TILE_SIZE * tan(rayAngle);
	step.y *= (raytemp->face.u && step.y > 0) ? -1 : 1;
	step.y *= (raytemp->face.d && step.y < 0) ? -1 : 1;
	raytemp->nextTouch.x = intercept.x;
	raytemp->nextTouch.y = intercept.y;
	ft_find_wall(data, raytemp, toCheck, step, 1);
	return (TRUE);
}

// initializes raytemp struct with basic values
int		ft_init_raytemp(t_rays *raytemp, float rayAngle)
{
	*raytemp = (t_rays) {0};  // fill the struct with zeroes
	raytemp->face.d = rayAngle > 0 && rayAngle < PI;
	raytemp->face.u = !(raytemp->face.d);
	raytemp->face.r = rayAngle < (0.5 * PI) || rayAngle > (1.5 * PI);
	raytemp->face.l = !(raytemp->face.r);
	return (TRUE);
}

// calculates the distance between two coordinates x and y
float	ft_distance(t_coord coord_a, t_coord coord_b)
{
	t_coord rslt;

	rslt.x = coord_b.x - coord_a.x;
	rslt.x *= rslt.x;
	rslt.y = coord_b.y - coord_a.y;
	rslt.y *= rslt.y;
	return sqrt(rslt.x + rslt.y);
}

// copies the values from raytemp to actual ray struct array position
int		ft_fill_ray(t_data *data, t_rays *raytemp, int is_vert, int stripId)
{
	data->rays[stripId].distance = ft_distance(data->player.playerspr.pos, raytemp->wallhit);
	data->rays[stripId].wallhit.x = raytemp->wallhit.x;
	data->rays[stripId].wallhit.y = raytemp->wallhit.y;
	data->rays[stripId].wallHitContent = raytemp->wallHitContent;
	data->rays[stripId].face.u = raytemp->face.u;
	data->rays[stripId].face.d = raytemp->face.d;
	data->rays[stripId].face.l = raytemp->face.l;
	data->rays[stripId].face.r = raytemp->face.r;
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
	distance.x = raytemp_h.foundwall ? ft_distance(data->player.playerspr.pos, raytemp_h.wallhit) : __FLT_MAX__;
	distance.y = raytemp_v.foundwall ? ft_distance(data->player.playerspr.pos, raytemp_v.wallhit) : __FLT_MAX__;
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
	//rayAngle = data->player.rotationAngle - (FOV / 2);
	rayAngle = data->player.rotationAngle + atan((stripId - (NUM_RAYS / 2)) / DIST_PROJ_PLANE);
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

	if (data->rays[projection->i].verticalhit)
		textOffsetX = (int)data->rays[projection->i].wallhit.y % TILE_SIZE;
	else
		textOffsetX = (int)data->rays[projection->i].wallhit.x % TILE_SIZE;
	while (projection->y < projection->column_bottom)
	{
		distanceFromTop = (projection->y + (projection->strip_h / 2) - (SCREENH / 2));
		textOffsetY = distanceFromTop * ((float)data->texture[tex_ind].size.h / projection->strip_h);
		data->colorBuffer[(SCREENW * projection->y) + projection->i] = (uint32_t)data->texture[tex_ind].buffer[(data->texture[tex_ind].size.w * textOffsetY) + textOffsetX];
		projection->y++;
	}
	return (TRUE);
}

// generates the 3D projection using raycasting
void	ft_gen_3d_proj(t_data *data)
{
	t_3dproj	projection;

	projection.i = 0;
	while (projection.i < NUM_RAYS)
	{
		projection.y = 0;
		projection.c_distance = data->rays[projection.i].distance * cos(data->rays[projection.i].angle - data->player.rotationAngle);
		projection.proj_wall_h = (TILE_SIZE / projection.c_distance) * DIST_PROJ_PLANE;
		projection.strip_h = (int)projection.proj_wall_h;
		projection.column_top = (SCREENH / 2) - (floor(projection.proj_wall_h) / 2);
		projection.column_top = projection.column_top < 0 ? 0 : projection.column_top;
		projection.column_bottom = (SCREENH / 2) + (projection.proj_wall_h / 2);
		projection.column_bottom = projection.column_bottom > SCREENH ? SCREENH : projection.column_bottom;
		while (projection.y < projection.column_top)
			data->colorBuffer[(SCREENW * projection.y++) + projection.i] = ft_crt_trgb(255, 192, 192, 192);
		
		if (data->rays[projection.i].verticalhit)
			if (data->rays[projection.i].face.l)
				ft_project_texture(data, &projection, 0);
			else
				ft_project_texture(data, &projection, 1);
		else
			if (data->rays[projection.i].face.u)
				ft_project_texture(data, &projection, 2);
			else
				ft_project_texture(data, &projection, 3);

		while (projection.y < SCREENH)
			data->colorBuffer[(SCREENW * projection.y++) + projection.i] = ft_crt_trgb(255, 62, 64, 64);
		projection.i++;
	}
}

// sorts sprites order by distance from player
void	ft_sort_sprites(t_data *data)
{
	t_sprite	temp;
	int			i;

	i = SPRITE_COUNT - 1;
	while (i > 0)
	{
		if (data->sprite[i].distance > data->sprite[i - 1].distance)
		{
			temp = data->sprite[i];
			data->sprite[i] = data->sprite[i - 1];
			data->sprite[i - 1] = temp;
			i = SPRITE_COUNT - 1;
		}
		else
			i--;
	}
}

// draws the sprite on screen
void	ft_draw_sprite(t_data *data, int i)
{
	t_coord		t;
	t_coord		in;
	t_coord		c;
	uint32_t	cor;
	int			ray_sprite;

	in.x = data->sprite->fact - (data->sprite[i].size.w / 2);
	in.y = (SCREENH / 2) - (data->sprite[i].size.h / 2);
	c.x = 0;
	while (c.x < data->sprite[i].size.w)
	{
		c.y = 0;
		t.x = c.x * data->sprite[i].texture.size.w / data->sprite[i].size.w;
		ray_sprite = (in.x + c.x);
		while (c.y < data->sprite[i].size.h)
		{
			t.y = c.y * data->sprite[i].texture.size.h / data->sprite[i].size.h;
			if (!(ft_invalid_area(data, (in.x + c.x), (in.y + c.y))) && data->sprite[i].distance < data->rays[ray_sprite].distance)
			{
				cor = *(uint32_t*)(data->sprite[i].texture.instance.addr + (int)((t.y * data->sprite[i].texture.size.w) + t.x) * 4);
				if (cor != 0)
					ft_print_pixel(data, (in.x + c.x), (in.y + c.y), cor);
			}
			c.y++;
		}
		c.x++;
	}
}

// calculates sprite size and position on screen
void	ft_update_sprite(t_data *data, int i)
{
	t_sprite sprite;

	sprite = data->sprite[i];
	sprite.angle = atan2(
		(sprite.pos.y - data->player.playerspr.pos.y),
		(sprite.pos.y - data->player.playerspr.pos.y)
	);
	sprite.angle_dif = (data->player.rotationAngle - sprite.angle);
	sprite.angle_dif = ft_normalize_angle(sprite.angle_dif);
	sprite.angle_dif = fabs(sprite.angle_dif);
	sprite.distance *= (cos(sprite.angle_dif));
	if (sprite.angle_dif < (FOV / 2 + 0.5))
	{
		sprite.size.h = (TILE_SIZE * DIST_PROJ_PLANE / sprite.distance);
		sprite.size.w = (sprite.size.h * sprite.texture.size.w / sprite.texture.size.h);
		sprite.fact = tan(sprite.angle - data->player.rotationAngle) * DIST_PROJ_PLANE + (SCREENW / 2);
	}
	data->sprite[i] = sprite;
}

// calculates each sprite distance from player
void	ft_sprite_dist(t_data *data)
{
	int i = 0;
	
	while (i < SPRITE_COUNT)
	{
		data->sprite[i].distance = ft_distance(data->player.playerspr.pos, data->sprite[i].pos);
		i++;
	}
}

// handles sprites
void	ft_sprites(t_data *data)
{
	int		i = 0;

	ft_sprite_dist(data);
	ft_sort_sprites(data);
	while (i < SPRITE_COUNT)
	{
		ft_update_sprite(data, i);
		if (data->sprite[i].angle_dif < (FOV / 2 + 0.5))
			ft_draw_sprite(data, i);
		i++;
	}
}