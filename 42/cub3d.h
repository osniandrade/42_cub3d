/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarlos- <ocarlos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 08:55:43 by ocarlos-          #+#    #+#             */
/*   Updated: 2021/02/04 10:17:03 by ocarlos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define TRUE			1
#define FALSE			0

#define GAMESPEED		0.2  // only values lower than 1.0
#define INIT_WALKSPD	3 * GAMESPEED
#define INIT_TURNSPD	4.5 * GAMESPEED
#define MOVESPEED		1
#define KEYPRESS		2
#define KEYRELEASE		3

// keycodes
#define UP				65362
#define DOWN			65364
#define RIGHT			65363
#define LEFT			65361
#define ESC				65307

#define PI				3.14159265

#define TILE_SIZE		32
#define MAP_ROWS		13
#define MAP_COLS		20
#define MAP_SCALE		1.0  // only values lower than 1.0
#define PLAYERSIZE		(TILE_SIZE / 2) * MAP_SCALE

#define SCREENW			(MAP_COLS * TILE_SIZE)
#define SCREENH			(MAP_ROWS * TILE_SIZE)

#define NUM_RAYS		15  //SCREENW
#define FOV				(60 * (PI / 180))

#include <mlx.h>
#include <stdlib.h>
#include <math.h>
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
	int		rayup;
	int		raydown;
	int		rayleft;
	int		rayright;
	int		wallHitContent;
	int		foundwall;
	int		wallcontent;
	t_coord	wallhit;
	t_coord	nextTouch;
	t_img	rayspr;
}			t_rays;

typedef struct	s_data
{
	void			*mlx;
	void			*mlx_win;
	int				width, height;
	int				up, down, left, right;
	int				(*maptable)[MAP_ROWS][MAP_COLS];
	t_img			tile;
	t_rays			rays[NUM_RAYS];
	t_playerdata	player;
}					t_data;

int		ft_init_win(t_data *data);
void	ft_init_img(t_data *data);
void	ft_setup(t_data *data, int argc, char **argv);
int		ft_key_press(int keycode, t_data *data);
int		ft_key_release(int keycode, t_data *data);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		ft_draw_line(t_data *data, t_coord i_pos, t_coord f_pos, int color);
int		ft_draw_rect(t_data *data, int h, int w, int color);
int		ft_draw_player(t_data *data, int color);
int		ft_erase(t_data *data);
int		ft_render_map(t_data *data);
int		ft_render_player(t_data *data);
int		ft_draw(t_data *data);
int		ft_renderray(t_data *data);
int		ft_invalidarea(t_data *data, float x, float y);
float	ft_normalizeangle(float angle);
int		ft_update(t_data *data);
int		ft_move(t_data *data);
int		ft_findwall(t_data *data, t_rays *raytemp, t_coord toCheck, t_coord step, int is_vert);
int		ft_h_intersection(t_data *data, t_rays *raytemp, t_coord intercept, t_coord step, float rayAngle);
int		ft_v_intersection(t_data *data, t_rays *raytemp, t_coord intercept, t_coord step, float rayAngle);
int		ft_fillray(t_data *data, t_rays *raytemp, int is_vert, int stripId);
int		ft_raycast(t_data *data, float rayAngle, int stripId);
int		ft_cast_all_rays(t_data *data);

int		ft_crt_trgb(int t, int r, int g, int b);
int		ft_get_t(int trgb);
int		ft_get_r(int trgb);
int		ft_get_g(int trgb);
int		ft_get_b(int trgb);
int		ft_maparray(int argc, char **argv);

int		ft_test_line_draw(t_data *data);
int     ft_test_collision(t_data *data);