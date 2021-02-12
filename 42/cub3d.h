/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarlos- <ocarlos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 08:55:43 by ocarlos-          #+#    #+#             */
/*   Updated: 2021/02/12 15:28:36 by ocarlos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define TRUE			1
#define FALSE			0

#define GAMESPEED		0.5  // only values lower than 1.0
#define INIT_WALKSPD	10 * GAMESPEED
#define INIT_TURNSPD	6 * GAMESPEED
#define MOVESPEED		1
#define KEYPRESS		2
#define KEYRELEASE		3
#define TEXTURE_COUNT	2

// keycodes
#define UP				65362
#define DOWN			65364
#define RIGHT			65363
#define LEFT			65361
#define ESC				65307

#define PI				3.14159265

#define TILE_SIZE		64
#define	TEXTURE_W		64
#define TEXTURE_H		64
#define MAP_ROWS		13
#define MAP_COLS		20
#define MAP_SCALE		0.25  // only values lower than 1.0
#define PLAYERSIZE		(TILE_SIZE / 2) * MAP_SCALE

#define SCREENW			(MAP_COLS * TILE_SIZE)
#define SCREENH			(MAP_ROWS * TILE_SIZE)

#define NUM_RAYS		SCREENW
#define FOV				(60 * (PI / 180))

// text purposes
#define	TEXTURE_INDEX	0

#include <mlx.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>  // REMOVE LATER
#include "get_next_line.h"

typedef struct s_coord
{
	float x;
	float y;
}		t_coord;

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

typedef struct s_playerdata
{
	int		turnDirection;  // -1 for left, +1 for right
    int		walkDirection;  // -1 for back, +1 for front
    float	rotationAngle;
    float	walkSpeed;
    float	turnSpeed;
	t_img	playerspr;
}			t_playerdata;

typedef struct s_rays
{
	float	angle;
	float	distance;
	int		verticalhit;
	int		face_up;
	int		face_down;
	int		face_left;
	int		face_right;
	int		wallHitContent;
	int		foundwall;
	int		wallcontent;
	t_coord	wallhit;
	t_coord	nextTouch;
	t_img	rayspr;
}			t_rays;

typedef struct s_texture
{
	int		colorArray[TEXTURE_H][TEXTURE_W];
}			t_texture;

typedef struct	s_data
{
	void			*mlx;
	void			*mlx_win;
	int				width, height;
	int				up, down, left, right;
	int				(*maptable)[MAP_ROWS][MAP_COLS];
	uint32_t		*colorBuffer[TEXTURE_COUNT];
	t_texture		texture[TEXTURE_COUNT];
	t_img			tile;
	t_rays			rays[NUM_RAYS];
	t_playerdata	player;
}					t_data;

typedef struct	s_3dproj
{
	int				column_top;
	int				column_bottom;
	int				strip_h;
	int				i;
	int				y;
	float			c_distance;
	float			dist_proj_plane;
	float			proj_wall_h;
}					t_3dproj;

int		ft_init_win(t_data *data);
void	ft_init_img(t_data *data);
void	ft_init_player(t_data *data);
void	ft_setup(t_data *data, int argc, char **argv);
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
float	ft_distance(t_data *data, t_rays *raytemp);
int		ft_fill_ray(t_data *data, t_rays *raytemp, int is_vert, int stripId);
int		ft_cast_ray(t_data *data, float rayAngle, int stripId);
int		ft_cast_all_rays(t_data *data);
int		ft_edit_colorbuffer(t_data *data, int print);
int		ft_project_texture(t_data *data, t_3dproj *projection, int tex_ind);
void	ft_gen_3d_proj(t_data *data, int tex_ind);

int		ft_crt_trgb(int t, int r, int g, int b);
int		ft_get_t(int trgb);
int		ft_get_r(int trgb);
int		ft_get_g(int trgb);
int		ft_get_b(int trgb);
int		ft_mapstats(int *map);
int		ft_maparray(int argc, char **argv);

int		ft_test_line_draw(t_data *data);
int     ft_test_collision(t_data *data);
int		ft_texture_gen(t_data *data, int pos);

