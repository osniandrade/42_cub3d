/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarlos- <ocarlos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 08:55:43 by ocarlos-          #+#    #+#             */
/*   Updated: 2021/01/14 09:26:01 by ocarlos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define TRUE		1
#define FALSE		0

#define GAMESPEED	0.05  // only values lower than 1.0
#define MOVESPEED	1
#define KEYPRESS	2
#define KEYRELEASE	3
#define FPS         1111111
// keycodes
#define UP			65362
#define DOWN		65364
#define RIGHT		65363
#define LEFT		65361
#define ESC			65307

#define PI          3.14159265

#define TILE_SIZE   32
#define MAP_ROWS    13
#define MAP_COLS    20
#define MAP_SCALE   1.0  // only values lower than 1.0
#define PLAYERSIZE	(TILE_SIZE / 2) * MAP_SCALE

#define SCREENW 	(MAP_COLS * TILE_SIZE)
#define SCREENH 	(MAP_ROWS * TILE_SIZE)



#include <mlx.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>  // REMOVE LATER
#include "get_next_line.h"

typedef struct s_coord
{
	int x;
	int y;
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

typedef struct	s_data
{
	void			*mlx;
	void			*mlx_win;
	int				width, height;
	int				up, down, left, right;
	int				(*maptable)[MAP_ROWS][MAP_COLS];
	t_img			tile;
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
int		ft_validarea(t_data *data, int step);
int		ft_update(t_data *data);
int		ft_move(t_data *data);

int		ft_crt_trgb(int t, int r, int g, int b);
int		ft_get_t(int trgb);
int		ft_get_r(int trgb);
int		ft_get_g(int trgb);
int		ft_get_b(int trgb);
int		ft_maparray(int argc, char **argv);

int		ft_test_line_draw(t_data *data);
int     ft_test_collision(t_data *data);