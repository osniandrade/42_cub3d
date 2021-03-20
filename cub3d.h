/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarlos- <ocarlos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 08:55:43 by ocarlos-          #+#    #+#             */
/*   Updated: 2021/03/20 17:32:56 by ocarlos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
#define MAP_SCALE		0.25  // only values lower than 1.0
#define PLAYERSIZE		((TILE_SIZE / 2) * MAP_SCALE)

#define FOV				(60 * (PI / 180))

#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <errno.h>
#include "minilibx/mlx.h"
#include "gnl/get_next_line.h"

#include <stdio.h>  // REMOVE LATER

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
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	t_sizedata		size;  // size (in pixels)
	t_coord			pos;
}			t_img;

typedef struct s_texture
{
	char		*path;
	t_img		instance;
	t_sizedata	size;
	uint32_t*	buffer;
}				t_texture;

typedef struct s_sprite
{
	float		distance;	// distance from player
	float		angle;		// angle in radians
	int			visible;	// 1 if sprite is visible, 0 if not
	t_texture	texture;	// sprite texture information
	t_coord		pos;		// sprite position on screen
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

typedef struct		s_filedata
{
	char			*tex_path[TEXTURE_COUNT];
	char			*spr_path[SPRITE_COUNT];
	char			plrdir;
	int				argcount;
	int				*map;
	int				rgbup[3];
	int				rgbdw[3];
	t_coord			plrstart;
	t_sizedata		scrsize;
	t_sizedata		mapsize;
}					t_filedata;
typedef struct		s_data
{
	void			*mlx;
	void			*mlx_win;
	int				visible_sprites[SPRITE_COUNT];
	int				*maptable;
	int				cei_color;
	int				flo_color;
	int				num_rays;
	float			d_proj_plane;
	t_filedata		cub;
	t_sprite		sprites[SPRITE_COUNT];
	t_texture		textures[TEXTURE_COUNT];
	t_dir			dir;
	t_sizedata		screensize;
	t_sizedata		mapsize;
	uint32_t		*colorBuffer;
	t_img			tile;
	t_rays			*rays;
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

typedef struct	s_sprproj
{
	int				x;
	int				y;
	int				x_ofst;
	int				y_ofst;
	int				dist_top;
	float			h;
	float			w;
	float			top_y;
	float			btm_y;
	float			angle;
	float			scr_x;
	float			left_x;
	float			right_x;
	float			texel_w;
	uint32_t		*buff;
	uint32_t		color;
	t_sizedata		texsize;
}					t_sprproj;

typedef struct	s_count
{
	int	x;
	int	y;
	int	i;
	int	j;
}				t_count;

typedef struct	s_drwline
{
	int			i_x;
	int			i_y;
	int			f_x;
	int			f_y;
	int			dx;
	int			sx;
	int			dy;
	int			sy;
	int			err;
	int			e2;
}				t_drwline;

// loadfile.c
// FILE DATA FUNCTIONS
int		ft_id_n_load(t_filedata *cubfile, char *line, int fd);
void	ft_load_cub_file(t_data *data, int argc, char **argv);

// functions.c
// INITIALIZATION
int		ft_init_win(t_data *data);
void	ft_init_img(t_data *data);
void	ft_init_map_size(t_data *data);
void	ft_init_player(t_data *data);
int		ft_init_sprite_struct(t_data *data);
int		ft_init_raytemp(t_rays *raytemp, float rayAngle);
int		ft_clear_colorbuffer(t_data *data, int init);
void	ft_init_drwstruct(t_drwline *c, t_coord *i_pos, t_coord *f_pos);
// LOADING
void	ft_load_file_paths(t_data *data);
void	ft_load_xpm_texture(t_data *data);
void	ft_load_xpm_sprite(t_data *data);
int		ft_loadmap(t_data *data);
int		ft_loadcolors(t_data *data);
// MAIN LOOP
void	ft_setup(t_data *data);
int		ft_update(t_data *data);
int		ft_draw(t_data *data);
// FINISH PROGRAM
void	ft_destroy_images(t_data *data);
void	ft_destroy(t_data *data, int f);
// KEYBOARD INTERACTIONS
int		ft_key_press(int keycode, t_data *data);
int		ft_key_release(int keycode, t_data *data);
// BASIC GRAPHIC FUNCTIONS
void	ft_print_pixel(t_data *data, int x, int y, int color);
int		ft_draw_line(t_data *data, t_coord i_pos, t_coord f_pos, int color, int resize);
int		ft_draw_rect(t_data *data, t_coord pos, t_sizedata size, int color, int resize);
void	ft_update_colorbuffer(t_data *data, t_coord pos, int color);
int		ft_print_colorbuffer(t_data *data);
// HELPER FUNCTIONS
float	ft_normalize_angle(float angle);
float	ft_normalize_angle2(float angle);
float	ft_sprite_arctan(t_data *data, int i);
float	ft_distance(t_coord coord_a, t_coord coord_b);
void	ft_reset_array(int *array, int i);
int		ft_pos(int w, int x, int y);
// MINIMAP DRAWING FUNCTIONS
int		ft_render_map(t_data *data);
int		ft_render_player(t_data *data);
int		ft_render_ray(t_data *data);
int		ft_render_minimap_sprite(t_data *data);
// TESTING FUNCTIONS
int		ft_invalid_screen_area(t_data *data, float x, float y);
int		ft_invalid_map_position(t_data *data, float x, float y);
int		ft_invalid_area(t_data *data, float x, float y);
// MOVEMENT FUNCTIONS
int		ft_move_player(t_data *data);
int		ft_player_direction(t_data *data);
int		ft_find_wall(t_data *data, t_rays *raytemp, t_coord toCheck, t_coord step, int is_vert);
// RAYCASTING FUNCTIONS
int		ft_h_intersection(t_data *data, t_rays *raytemp, t_coord intercept, t_coord step, float rayAngle);
int		ft_v_intersection(t_data *data, t_rays *raytemp, t_coord intercept, t_coord step, float rayAngle);
int		ft_fill_ray(t_data *data, t_rays *raytemp, int is_vert, int stripId);
int		ft_cast_ray(t_data *data, float rayAngle, int stripId);
int		ft_cast_all_rays(t_data *data);
int		ft_project_texture(t_data *data, t_3dproj *projection, int tex_ind);
void	ft_walltext(t_data *data, t_3dproj *prj);
void	ft_gen_3d_proj(t_data *data);
// SPRITE FUNCTIONS
void	ft_update_sprite(t_data *data);
void	ft_set_sprite(t_data *data, t_sprproj *sprite, int i);
void	ft_sprite_projection(t_data *data, t_sprproj *sprite, int i);
void	ft_draw_sprite(t_data *data);
int		ft_find_sprite(t_data *data);

// loadfile.c
// DATA LOADING FUNCTIONS
void	ft_ex_wrongdata(t_filedata *cubfile, char **clean_line, int fd);
void	ft_ex_wrongmap(t_filedata *cubfile, int f);
t_sizedata ft_ck_scrsize(t_filedata *cubfile, char **clean_line, int fd);
int		ft_ck_filetype(t_filedata *cubfile, char **clean_line, int fd);
void	ft_ck_rgbvalues(t_filedata *cubfile, char **clean_line, int *rgb, int fd);
int		ft_ck_mapdata(t_filedata *cubfile);
int		ft_ck_validchar(int *map, t_count c, t_filedata *cubfile);
int		ft_ck_sprite(t_filedata *cubfile, int *trgr);
void	ft_ck_validmap(t_filedata *cubfile);
void	ft_argtest(t_filedata *cubfile, char **clean_line, int fd);
int		ft_id_n_load(t_filedata *cubfile, char *line, int fd);
int		ft_testmapchar(char *line);
void	ft_getmapdata(t_filedata *cubfile, char *line, int fd);
void	ft_mapfill_1(t_filedata *cubfile, char *line, t_count *c);
void	ft_mapfill_2(t_filedata *cubfile, char *line, t_count *c);
void	ft_mapfill_3(t_filedata *cubfile, char *line, t_count *c);
void	ft_mapfill(t_filedata *cubfile, char *line, t_count *c);
void	ft_processmap(t_filedata *cubfile, char *line, int fd);
void	ft_load_cub_file(t_data *data, int argc, char **argv);

// helper.c
// HELPER
uint32_t		ft_crt_trgb(int t, int r, int g, int b);
uint32_t		ft_get_t(int trgb);
uint32_t		ft_get_r(int trgb);
uint32_t		ft_get_g(int trgb);
uint32_t		ft_get_b(int trgb);
size_t			ft_strlen(const char *s);
void			*ft_memcpy(void *dest, const void *src, size_t n);
char			*ft_strdup(const char *s1);
char			**ft_split(char const *s, char c);
int				ft_isdigit(int c);
int				ft_tstspc(const char ch);
int				ft_atoi(const char *str);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strchr(const char *s, int c);
int				ft_isascii(int c);

// testing.c
// TESTING
int		ft_test_init_sprite(t_data *data);
void	ft_t_printmap(t_filedata *cubfile);
