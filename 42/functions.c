/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarlos- <ocarlos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 16:09:30 by ocarlos-          #+#    #+#             */
/*   Updated: 2021/03/14 08:48:47 by ocarlos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*******************************************************************************
 * INITIALIZATION
 *******************************************************************************/

// initializes the main struct variables
int		ft_init_win(t_data *data)
{
	data->mlx = mlx_init();
	data->screensize.w = data->cub.scrsize.w;
	data->screensize.h = data->cub.scrsize.h;
	data->mlx_win = mlx_new_window(data->mlx, data->screensize.w, data->screensize.h, "A MAZE IN");
	return (TRUE);
}

// initializes a new image's struct
void	ft_init_img(t_data *data)
{
	t_img	imagem;

	imagem.img = mlx_new_image(data->mlx, data->screensize.w, data->screensize.h);
	imagem.addr = mlx_get_data_addr(imagem.img, &imagem.bits_per_pixel, 
									&imagem.line_length, &imagem.endian);
	imagem.pos.x = 0;
	imagem.pos.y = 0;
	imagem.size.w = TILE_SIZE;
	imagem.size.h = TILE_SIZE;
	data->tile = imagem;
}

// initializes the map size
void	ft_init_map_size(t_data *data)
{
	data->mapsize.h = data->cub.mapsize.h;
	data->mapsize.w = data->cub.mapsize.w;
	data->maptable = malloc(data->mapsize.w * data->mapsize.h * sizeof(int));
}

// initializes player data
void	ft_init_player(t_data *data)
{
	data->player.playerspr.pos.x = (data->screensize.w / 2);
	data->player.playerspr.pos.y = (data->screensize.h / 2);
	data->player.turnDirection = 0;
	data->player.walkDirection = 0;
	data->player.rotationAngle = PI / 2;
	data->player.walkSpeed = INIT_WALKSPD;
	data->player.turnSpeed = INIT_TURNSPD * (PI / 180);
}

// initializes sprite structs with zero
int		ft_init_sprite_struct(t_data *data)
{
	int i = 0;

	while (i < SPRITE_COUNT)
		data->sprites[i++] = (t_sprite) {0};  // fill the struct with zeroes
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

// initializes the colorbuffer
int		ft_clear_colorbuffer(t_data *data, int init)
// init = 0  - skips memory allocation
// init = 1  - allocates memory for buffer
{
	int i = 0;

	if(init == 1)
		data->colorBuffer = (uint32_t*) malloc(sizeof(uint32_t) * (uint32_t)data->screensize.w * (uint32_t)data->screensize.h);
	while(i < data->screensize.w * data->screensize.h)
	{
		data->colorBuffer[i++] = ft_crt_trgb(255, 0, 0, 0);
	}
	return (TRUE);
}

/*******************************************************************************
 * LOADING
 *******************************************************************************/

// loads texture paths from file to struct
void	ft_load_file_paths(t_data *data)
{
	int i = 0;

	while (i < TEXTURE_COUNT)
	{
		data->textures[i].path = data->cub.tex_path[i];
		i++;
	}
	i = 0;
	while (i < SPRITE_COUNT)
	{
		data->sprites[i].texture.path = data->cub.spr_path[i];
		i++;
	}
}

// loads xpm texture file into code
void	ft_load_xpm_texture(t_data *data)
{
	int i = 0;

	while (i < TEXTURE_COUNT)
	{
		data->textures[i].instance.img = mlx_xpm_file_to_image(
			data->mlx, 
			data->textures[i].path, 
			&data->textures[i].size.w, 
			&data->textures[i].size.h
		);
		data->textures[i].instance.addr = mlx_get_data_addr(
			data->textures[i].instance.img, 
			&(data->textures[i].instance.bits_per_pixel), 
			&(data->textures[i].instance.line_length), 
			&(data->textures[i].instance.endian)
		);
		data->textures[i].buffer = (uint32_t *) data->textures[i].instance.addr;
		i++;
	}
}

// loads sprite textures from array to a new image
void	ft_load_xpm_sprite(t_data *data)
{
	int i = 0;

	while (i < SPRITE_COUNT)
	{
		data->sprites[i].texture.instance.img = mlx_xpm_file_to_image(
			data->mlx,
			data->sprites[i].texture.path,
			&data->sprites[i].texture.size.w,
			&data->sprites[i].texture.size.h
		);
		data->sprites[i].texture.instance.addr = mlx_get_data_addr(
			data->sprites[i].texture.instance.img,
			&(data->sprites[i].texture.instance.bits_per_pixel),
			&(data->sprites[i].texture.instance.line_length),
			&(data->sprites[i].texture.instance.endian)
		);
		data->sprites[i].texture.buffer = (uint32_t *) data->sprites[i].texture.instance.addr;
		i++;
	}
}

// loads map into data structure
int		ft_loadmap(t_data *data)
{
	int x = 0;
	int y = 0;

	ft_init_map_size(data);
	while (y < data->mapsize.h)
	{
		x = 0;
		while (x < data->mapsize.w)
		{
			data->maptable[(data->mapsize.w * y) + x] = data->cub.map[(data->cub.mapsize.w * y) + x];  // what the fuck
			x++;
		}
		y++;
	}
	return (TRUE);
}

/*******************************************************************************
 * MAIN LOOP
 *******************************************************************************/

// initializes the setup for the main loop
void	ft_setup(t_data *data, int argc, char **argv)
{
	//ft_maparray(argc, argv);  // reads the map into the main struct
	ft_init_win(data);
	ft_clear_colorbuffer(data, 1);
	ft_init_img(data);
	ft_init_sprite_struct(data);
	ft_load_file_paths(data);
	ft_load_xpm_texture(data);
	ft_load_xpm_sprite(data);
	ft_loadmap(data);
	//ft_t_printmap(data);
	ft_init_player(data);
	ft_find_sprite(data);
}

// moves the image in the window
int		ft_update(t_data *data)
{
	ft_clear_colorbuffer(data, 0);
	ft_reset_array(data->visible_sprites, SPRITE_COUNT);
	ft_update_sprite(data);
	ft_player_direction(data);
	ft_cast_all_rays(data);
	ft_move_player(data);
	ft_gen_3d_proj(data);
	return (TRUE);
}

// draws elements in the window
int		ft_draw(t_data *data)
{
	ft_print_colorbuffer(data);
	ft_draw_sprite(data);
	//ft_render_map(data);
	//ft_render_ray(data);
	//ft_render_minimap_sprite(data);
	//ft_render_player(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->tile.img, 0, 0);
	return (TRUE);
}

/*******************************************************************************
 * FINISH PROGRAM
 *******************************************************************************/

// frees texture memory allocations
void	ft_destroy_images(t_data *data)
{
	int i = 0;

	mlx_destroy_image(data->mlx, data->tile.img);
	while (i < TEXTURE_COUNT)
	{
		mlx_destroy_image(data->mlx, data->textures[i].instance.img);
		i++;
	}
	i = 0;
	while (i < SPRITE_COUNT)
	{
		mlx_destroy_image(data->mlx, data->sprites[i].texture.instance.img);
		i++;
	}
}

// finishes the program
void	ft_destroy(t_data *data)
{
	free(data->colorBuffer);
	free(data->maptable);
	ft_destroy_images(data);
	mlx_destroy_window(data->mlx, data->mlx_win);
	exit(0);
}


/*******************************************************************************
 * KEYBOARD INTERACTIONS
 *******************************************************************************/

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


/*******************************************************************************
 * BASIC GRAPHIC FUNCTIONS
 *******************************************************************************/

// draws a pixel to the image buffer
void	ft_print_pixel(t_data *data, int x, int y, int color)
{
	char	*dst;
	x = round(x);
	y = round(y);

	if (y <= data->screensize.h && x <= data->screensize.w && x > 0 && y > 0)
	{
		dst = data->tile.addr + ((y * data->tile.line_length) + (x * (data->tile.bits_per_pixel / 8)));
		*(unsigned int *)dst = color;
	}
}

// draws a line from i_pos to f_pos in color (Bresenham's algorithm)
int		ft_draw_line(t_data *data, t_coord i_pos, t_coord f_pos, int color, int resize)
{
	int i_x = round(i_pos.x);
	int i_y = round(i_pos.y);
	int f_x = round(f_pos.x);
	int f_y = round(f_pos.y);	
	int dx = abs((int)f_x - (int)i_x);
	int sx = i_x < f_x ? 1 : -1;
	int dy = abs((int)f_y - (int)i_y);
	int sy = i_y < f_y ? 1 : -1;
	int err = (dx > dy ? dx : -dy) / 2;
	int e2;

	while(!(i_x == f_x && i_y == f_y))
	{
		if (resize)
			ft_print_pixel(data, i_x * MAP_SCALE, i_y * MAP_SCALE, color);
		else
			ft_print_pixel(data, i_x, i_y, color);
		e2 = err;
		if (e2 > -dx)
		{
			err -= dy;
			i_x += sx;
		}
		if (e2 < dy)
		{
			err += dx;
			i_y += sy;
		}
	}
	return (TRUE);
}

// draws a rectangle with defined height, width and color
int		ft_draw_rect(t_data *data, t_coord pos, t_sizedata size, int color, int resize)
{
	t_coord	i_pos, f_pos;

		i_pos.x = pos.x;
		i_pos.y = pos.y;
		f_pos.x = pos.x + size.w;
		f_pos.y = pos.y;
		while (i_pos.y <= pos.y + size.h)
		{
			ft_draw_line(data, i_pos, f_pos, color, resize);
			i_pos.y++;
			f_pos.y++;
		}
	return (TRUE);
}

// changes a pixel color in the colorbuffer
void	ft_update_colorbuffer(t_data *data, t_coord pos, int color)
{
	int x, y;

	x = floor(pos.x);
	y = floor(pos.y);
	data->colorBuffer[(data->screensize.w * y) + x] = color;
}

// renders the color buffer and fills it with color in parameter
int		ft_print_colorbuffer(t_data *data)
{
	int x;
	int y;

	x = 0;
	while (x < data->screensize.w)
	{
		y = 0;
		while (y < data->screensize.h)
		{
			ft_print_pixel(data, x, y, data->colorBuffer[(data->screensize.w * y) + x]);
			y++;
		}
		x++;
	}
	return (TRUE);
}

/*******************************************************************************
 * HELPER FUNCTIONS
 *******************************************************************************/

// normalize angle between 0 and 360
float	ft_normalize_angle(float angle) 
{
	angle = remainder(angle, PI * 2);
	if (angle < 0) 
	{
		angle = (2 * PI) + angle;
	}
	return (angle);
}

// normalize angle between 0 and 180
float	ft_normalize_angle2(float angle)
{
	if (angle > PI)
		angle -= PI * 2;
	if (angle < -PI)
		angle += PI * 2;
	return (angle);
}

// gets the arc tangent of a sprite relative to player position
float	ft_sprite_arctan(t_data *data, int i)
{
	t_coord		sprite = data->sprites[i].pos;
	t_coord		player = data->player.playerspr.pos;
	t_sizedata	sprsize = data->sprites[i].texture.size;
	
	return atan2(
		//sprite.y - player.y,
		//sprite.x - player.x
		(sprite.y + (sprsize.h / 2)) - player.y,
		(sprite.x + (sprsize.w / 2)) - player.x
	);
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

// resets every position in the array to 0
void	ft_reset_array(int *array, int i)
{
	while(i >= 0)
	{
		array[i--] = 9999;
	}
}

/*******************************************************************************
 * MINIMAP DRAWING FUNCTIONS
 *******************************************************************************/

// renders map
int		ft_render_map(t_data *data)
{
	int tileColor;
	int i = 0;
	int j = 0;

	while (i < data->mapsize.h)
	{
		while (j < data->mapsize.w)
		{
			data->tile.pos.x = (j * data->tile.size.w);
			data->tile.pos.y = (i * data->tile.size.w);
			tileColor = (data->maptable[(data->mapsize.w * i) + j] == 1) ? ft_crt_trgb(0,255,255,255) : 0;
			ft_draw_rect(data, data->tile.pos, data->tile.size, tileColor, 1);
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
	t_coord  f_pos;

	f_pos.x = data->player.playerspr.pos.x + cos(data->player.rotationAngle) * PLAYERSIZE;
	f_pos.y = data->player.playerspr.pos.y + sin(data->player.rotationAngle) * PLAYERSIZE;
	ft_draw_line(data, data->player.playerspr.pos, f_pos, ft_crt_trgb(0, 255, 0, 255), 1);
	data->player.walkDirection = 0;
	data->player.turnDirection = 0;
	return (TRUE);
}

// renders all rays from rays array on screen
int		ft_render_ray(t_data *data)
{
	int		ray;
	int		color;

	ray = 0;
	color = ft_crt_trgb(255, 0, 0, 255);
	while (ray < NUM_RAYS)
	{
		ft_draw_line(data, data->player.playerspr.pos, data->rays[ray].wallhit, color, 1);
		ray += 50;
	}
	return (TRUE);
}

// renders sprites in minimap
int		ft_render_minimap_sprite(t_data *data)
{
	int i = 0;

	while (i < SPRITE_COUNT)
	{
		ft_draw_rect(
			data, 
			data->sprites[i].pos, 
			data->sprites[i].texture.size, 
			(data->sprites[i].visible) ? ft_crt_trgb(0,0,255,0) : ft_crt_trgb(0,255,0,0),
			1
		);
		i++;
	}
	return (TRUE);
}

/*******************************************************************************
 * TESTING FUNCTIONS
 *******************************************************************************/

// checks if image is in drawable area, uses "step" as increment
int		ft_invalid_screen_area(t_data *data, float x, float y)
{
	if (x < 0 || x > data->screensize.w || y < 0  || y > data->screensize.h)
		return (TRUE);
	else
		return (FALSE);
}

// checks if screen position is valid
int		ft_invalid_map_position(t_data *data, float x, float y)
{
	int mapgridx = floor(x / data->tile.size.w);
	int mapgridy = floor(y / data->tile.size.w);
	
	if (data->maptable[(data->mapsize.w * mapgridy) + mapgridx] != 0)
		return (TRUE);
	else
		return (FALSE);
}

// checks both screen and map position
int		ft_invalid_area(t_data *data, float x, float y)
{
	if (ft_invalid_screen_area(data, x, y))
		return (TRUE);
	if (ft_invalid_map_position(data, x, y))
		return (TRUE);
	else
		return (FALSE);
}


/*******************************************************************************
 * MOVEMENT FUNCTIONS
 *******************************************************************************/

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

// loops until a wall is found - 0 for horizontal check and 1 for vertical check
int		ft_find_wall(t_data *data, t_rays *raytemp, t_coord toCheck, t_coord step, int is_vert)
{
	int		mapcontent;
	int		corr_x;
	int		corr_y;

	while (raytemp->nextTouch.x >= 0 && raytemp->nextTouch.x <= data->screensize.w && raytemp->nextTouch.y > 0 && raytemp->nextTouch.y <= data->screensize.h)
	{
		toCheck.x = raytemp->nextTouch.x;
		toCheck.y = raytemp->nextTouch.y;
		if (is_vert)
			toCheck.x += (raytemp->face.l ? -1 : 0);
		else
			toCheck.y += (raytemp->face.u ? -1 : 0);
		corr_x = (int)floor(toCheck.x / data->tile.size.w);
		corr_y = (int)floor(toCheck.y / data->tile.size.w);
		mapcontent = data->maptable[(corr_y * data->mapsize.w) + corr_x];
		if (ft_invalid_area(data, toCheck.x, toCheck.y) && (mapcontent == 1))
		{
			raytemp->wallhit.x = raytemp->nextTouch.x;
			raytemp->wallhit.y = raytemp->nextTouch.y;
			raytemp->wallcontent = mapcontent;
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


/*******************************************************************************
 * RAYCASTING FUNCTIONS
 *******************************************************************************/

// calculates horizontal ray intersection on the grid
int		ft_h_intersection(t_data *data, t_rays *raytemp, t_coord intercept, t_coord step, float rayAngle)
{
	t_coord	toCheck;

	raytemp->wallhit.x = 0;
	raytemp->wallhit.y = 0;
	intercept.y = floor(data->player.playerspr.pos.y / data->tile.size.w) * data->tile.size.w;
	intercept.y += raytemp->face.d ? data->tile.size.w : 0;
	intercept.x = data->player.playerspr.pos.x + (intercept.y - data->player.playerspr.pos.y) / tan(rayAngle);
	step.y = data->tile.size.w;
	step.y *= raytemp->face.u ? -1 : 1;
	step.x = data->tile.size.w / tan(rayAngle);
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
	intercept.x = floor(data->player.playerspr.pos.x / data->tile.size.w) * data->tile.size.w;
	intercept.x += raytemp->face.r ? data->tile.size.w : 0;
	intercept.y = data->player.playerspr.pos.y + (intercept.x - data->player.playerspr.pos.x) * tan(rayAngle);
	step.x = data->tile.size.w;
	step.x *= raytemp->face.l ? -1 : 1;
	step.y = data->tile.size.w * tan(rayAngle);
	step.y *= (raytemp->face.u && step.y > 0) ? -1 : 1;
	step.y *= (raytemp->face.d && step.y < 0) ? -1 : 1;
	raytemp->nextTouch.x = intercept.x;
	raytemp->nextTouch.y = intercept.y;
	ft_find_wall(data, raytemp, toCheck, step, 1);
	return (TRUE);
}

// copies the values from raytemp to actual ray struct array position
int		ft_fill_ray(t_data *data, t_rays *raytemp, int is_vert, int stripId)
{
	data->rays[stripId].distance = ft_distance(data->player.playerspr.pos, raytemp->wallhit);
	data->rays[stripId].wallhit.x = raytemp->wallhit.x;
	data->rays[stripId].wallhit.y = raytemp->wallhit.y;
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

// projects the wall textures to each strip of each wall
int		ft_project_texture(t_data *data, t_3dproj *projection, int tex_ind)
{
	int		textOffsetY;
	int		textOffsetX;
	int		distanceFromTop;

	if (data->rays[projection->i].verticalhit)
		textOffsetX = (int)data->rays[projection->i].wallhit.y % data->tile.size.w;
	else
		textOffsetX = (int)data->rays[projection->i].wallhit.x % data->tile.size.w;
	while (projection->y < projection->column_bottom)
	{
		distanceFromTop = (projection->y + (projection->strip_h / 2) - (data->screensize.h / 2));
		textOffsetY = distanceFromTop * ((float)data->textures[tex_ind].size.h / projection->strip_h);
		data->colorBuffer[(data->screensize.w * projection->y) + projection->i] = (uint32_t)data->textures[tex_ind].buffer[(data->textures[tex_ind].size.w * textOffsetY) + textOffsetX];
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
		projection.proj_wall_h = (data->tile.size.w / projection.c_distance) * DIST_PROJ_PLANE;
		projection.strip_h = (int)projection.proj_wall_h;
		projection.column_top = (data->screensize.h / 2) - (floor(projection.proj_wall_h) / 2);
		projection.column_top = projection.column_top < 0 ? 0 : projection.column_top;
		projection.column_bottom = (data->screensize.h / 2) + (projection.proj_wall_h / 2);
		projection.column_bottom = projection.column_bottom > data->screensize.h ? data->screensize.h : projection.column_bottom;
		while (projection.y < projection.column_top)
			data->colorBuffer[(data->screensize.w * projection.y++) + projection.i] = ft_crt_trgb(255, 192, 192, 192);
		
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

		while (projection.y < data->screensize.h)
			data->colorBuffer[(data->screensize.w * projection.y++) + projection.i] = ft_crt_trgb(255, 62, 64, 64);
		projection.i++;
	}
}

/*******************************************************************************
 * SPRITE FUNCTIONS
 *******************************************************************************/

// draws the sprite on screen
void	ft_update_sprite(t_data *data)
{
	int i;
	int sprc;
	float sprite_player_angle;

	i = 0;
	sprc = 0;
	while (i < SPRITE_COUNT)
	{
		sprite_player_angle = data->player.rotationAngle - ft_sprite_arctan(data, i);
		sprite_player_angle = fabs(ft_normalize_angle2(sprite_player_angle));
		if (sprite_player_angle < (FOV / 2) + 0.2)
		{
			data->sprites[i].visible = 1;
			data->sprites[i].angle = sprite_player_angle;
			data->sprites[i].distance = ft_distance(data->sprites[i].pos, data->player.playerspr.pos);
			data->visible_sprites[sprc++] = i;
		}
		else
		{
			data->sprites[i].visible = 0;
		}
		i++;
	}
}

// calculates the initial values of the sprite projection
void	ft_set_sprite(t_data *data, t_sprproj *sprite, int i)
{
	sprite->texsize = data->sprites[i].texture.size;
	sprite->h = (sprite->texsize.h / data->sprites[i].distance) * DIST_PROJ_PLANE;
	sprite->w = (sprite->texsize.w / data->sprites[i].distance) * DIST_PROJ_PLANE;
	sprite->top_y = (data->screensize.h / 2) - (sprite->h / 2);
	sprite->top_y = (sprite->top_y < 0) ? 0 : sprite->top_y;
	sprite->btm_y = (data->screensize.h / 2) + (sprite->h / 2);
	sprite->btm_y = (sprite->btm_y > data->screensize.h) ? data->screensize.h : sprite->btm_y;
	sprite->angle = ft_sprite_arctan(data, i) - data->player.rotationAngle;
	sprite->scr_x = tan(sprite->angle) * DIST_PROJ_PLANE;
	sprite->left_x = (data->screensize.w / 2) + sprite->scr_x - (sprite->w / 2);
	sprite->right_x = sprite->left_x + sprite->w;
	sprite->x = sprite->left_x;
}

// calculates the sprite projection and prints it on screen
void	ft_sprite_projection(t_data *data, t_sprproj *sprite, int i)
{
	while (sprite->x < sprite->right_x)
	{
		sprite->texel_w = (sprite->texsize.w / sprite->w);
		sprite->x_ofst = (sprite->x - sprite->left_x) * sprite->texel_w;
		sprite->y = sprite->top_y;
		while (sprite->y < sprite->btm_y)
		{
			if (!(ft_invalid_screen_area(data, (float)sprite->x, (float)sprite->y)))
			{
				sprite->dist_top = sprite->y + (sprite->h / 2) - (data->screensize.h / 2);
				sprite->y_ofst = sprite->dist_top * (sprite->texsize.h / sprite->h);
				sprite->buff = (uint32_t*)data->sprites[i].texture.buffer;
				sprite->color = sprite->buff[(sprite->texsize.w * sprite->y_ofst) + sprite->x_ofst];
				if (sprite->color != data->sprites[i].texture.buffer[0])
					if (data->sprites[i].distance < data->rays[sprite->x].distance)
						ft_print_pixel(data, sprite->x, sprite->y, sprite->color);
			}
			sprite->y++;
		}
		sprite->x++;
	}
}

// calculates sprite size and position on screen
void	ft_draw_sprite(t_data *data)
{
	int i;
	int j;
	t_sprproj	sprite;
	
	i = 0;
	j = 0;
	while (i < SPRITE_COUNT)
	{
		if (i == data->visible_sprites[j])
		{
			ft_set_sprite(data, &sprite, i);
			ft_sprite_projection(data, &sprite, i);
			j++;
		}
		i++;
	}
}

// finds the sprite on the map
int		ft_find_sprite(t_data *data)
{
	int x = 0;
	int y;
	int i = 0;

	while (i < SPRITE_COUNT)
	{
		while (x < data->mapsize.h)
		{
			y = 0;
			while (y < data->mapsize.w)
			{
				if (data->maptable[(data->mapsize.w * y) + x] == 2)
				{
					data->sprites[i].pos.x = x * data->tile.size.h;
					data->sprites[i].pos.y = y * data->tile.size.w;
					return (TRUE);
				}
				y++;
			}
			x++;
		}
		i++;
	}
	return (FALSE);
}
