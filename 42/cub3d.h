/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarlos- <ocarlos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 08:55:43 by ocarlos-          #+#    #+#             */
/*   Updated: 2021/02/25 11:02:10 by ocarlos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#define TRUE			1
#define FALSE			0

#define GAMESPEED		0.5  // only values lower than 1.0
#define INIT_WALKSPD	(16 * GAMESPEED)
#define INIT_TURNSPD	(6 * GAMESPEED)
#define MOVESPEED		1
#define KEYPRESS		2
#define KEYRELEASE		3
#define TEXTURE_COUNT	4
#define SPRITE_COUNT	1

// keycodes
#define UP				65362
#define DOWN			65364
#define RIGHT			65363
#define LEFT			65361
#define ESC				65307

#define PI				3.14159265

#define TILE_SIZE		64
#define MAP_ROWS		13
#define MAP_COLS		20
#define MAP_SCALE		0.25  // only values lower than 1.0
#define PLAYERSIZE		((TILE_SIZE / 2) * MAP_SCALE)

#define SCREENW			(MAP_COLS * TILE_SIZE)
#define SCREENH			(MAP_ROWS * TILE_SIZE)

#define NUM_RAYS		SCREENW
#define FOV				(60 * (PI / 180))
#define DIST_PROJ_PLANE ((SCREENW / 2) / tan(FOV / 2))

#include "minilibx/mlx.h"
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>  // REMOVE LATER
#include "get_next_line.h"

typedef struct s_coord
{
	float	x;
	float	y;
}			t_coord;

typedef struct s_sizedata
{
	int		h;
	int		w;
}			t_sizedata;

typedef struct s_dir
{
	int		u;
	int		d;
	int		l;
	int		r;
}			t_dir;

typedef struct s_img
{
	int		s;  // size (in pixels)
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	t_coord	pos;
}			t_img;

typedef struct s_texture
{
	t_img		instance;
	t_sizedata	size;
	uint32_t*	buffer;
}				t_texture;

typedef struct s_sprite
{
	float		distance;	// distance from player
	float		angle;		// angle in radians
	float		angle_dif;	// angle difference in comparison with player
	int			fact;		// 
	t_texture	texture;
	t_sizedata	size;
	t_coord		pos;
}				t_sprite;
typedef struct s_playerdata
{
	int		turnDirection;  // -1 for left, +1 for right
    int		walkDirection;  // -1 for back, +1 for front
    float	rotationAngle;	// rotation angle info (in radians)
    float	walkSpeed;		// walk speed multiplier
    float	turnSpeed;		// turn speed multiplier
	t_img	playerspr;		// player sprite info (for minimap)
}			t_playerdata;

typedef struct s_rays
{
	float	angle;			// ray angle in radians
	float	distance;		// distance from wall
	int		verticalhit;	// hit on wall was vertical
	int		foundwall;		// if ray found a wall
	int		wallcontent;	// content of wall found by ray
	t_dir	face;			// direction ray is facing
	t_coord	wallhit;		// coordinates of wall hit
	t_coord	nextTouch;		// second intersection of ray with wall
	t_img	rayspr;			// ray sprite info (for minimap)
}			t_rays;

typedef struct	s_data
{
	void			*mlx;
	void			*mlx_win;
	int				(*maptable)[MAP_ROWS][MAP_COLS];
	char			*texturepaths[TEXTURE_COUNT];
	char			*spritepaths[SPRITE_COUNT];
	t_sprite		sprite[SPRITE_COUNT];
	t_dir			dir;
	t_sizedata		size;
	uint32_t		*colorBuffer;
	t_texture		texture[TEXTURE_COUNT];
	t_img			tile;
	t_rays			rays[NUM_RAYS];
	t_playerdata	player;
}					t_data;

typedef struct	s_3dproj
{
	int				column_top;		// y coord of the top of the pixel column in 3d projection
	int				column_bottom;	// y coord of the bottom of pixel column
	int				strip_h;		// heigth of the pixel column
	int				i;
	int				y;
	float			c_distance;		// distance from player
	float			proj_wall_h;	// heigth of the pojected wall in pixels
}					t_3dproj;

int		ft_init_win(t_data *data);
void	ft_init_img(t_data *data);
void	ft_load_texture_paths(t_data *data);
void	ft_load_file_paths(char **dstpath, char **srcpath, int i);
void	ft_load_xpm_texture(t_data *data);
void	ft_load_xpm_sprite(t_data *data);
void	ft_init_player(t_data *data);
int		ft_loadmap(t_data *data);
int		ft_init_struct(t_data *data);
void	ft_setup(t_data *data, int argc, char **argv);
void	ft_destroy_images(t_data *data);
void	ft_destroy(t_data *data);
int		ft_key_press(int keycode, t_data *data);
int		ft_key_release(int keycode, t_data *data);
void	ft_print_pixel(t_data *data, int x, int y, int color);
int		ft_draw_line(t_data *data, t_coord i_pos, t_coord f_pos, int color);
int		ft_draw_rect(t_data *data, int h, int w, int color);
int		ft_draw_player(t_data *data, int color);
int		ft_invalid_area(t_data *data, float x, float y);
float	ft_normalize_angle(float angle);
int		ft_move_player(t_data *data);
int		ft_render_map(t_data *data);
int		ft_render_player(t_data *data);
int		ft_render_ray(t_data *data);
int		ft_draw(t_data *data);
int		ft_player_direction(t_data *data);
int		ft_update(t_data *data);
int		ft_find_wall(t_data *data, t_rays *raytemp, t_coord toCheck, t_coord step, int is_vert);
int		ft_h_intersection(t_data *data, t_rays *raytemp, t_coord intercept, t_coord step, float rayAngle);
int		ft_v_intersection(t_data *data, t_rays *raytemp, t_coord intercept, t_coord step, float rayAngle);
int		ft_init_raytemp(t_rays *raytemp, float rayAngle);
float	ft_distance(t_coord coord_a, t_coord coord_b);
int		ft_fill_ray(t_data *data, t_rays *raytemp, int is_vert, int stripId);
int		ft_cast_ray(t_data *data, float rayAngle, int stripId);
int		ft_cast_all_rays(t_data *data);
int		ft_print_colorbuffer(t_data *data, int print);
int		ft_project_texture(t_data *data, t_3dproj *projection, int tex_ind);
void	ft_gen_3d_proj(t_data *data);
int		ft_find_sprite(t_data *data);
void	ft_sort_sprites(t_data *data);
void	ft_draw_sprite(t_data *data);
void	ft_update_sprite(t_data *data);
void	ft_sprite_dist(t_data *data);
void	ft_sprites_update(t_data *data);

uint32_t		ft_crt_trgb(int t, int r, int g, int b);
uint32_t		ft_get_t(int trgb);
uint32_t		ft_get_r(int trgb);
uint32_t		ft_get_g(int trgb);
uint32_t		ft_get_b(int trgb);
int		ft_mapstats(int *map);
int		ft_maparray(int argc, char **argv);

int		ft_test_line_draw(t_data *data);
int     ft_test_collision(t_data *data);
// int		ft_texture_gen(t_data *data, int pos);

