/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarlos- <ocarlos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 08:55:43 by ocarlos-          #+#    #+#             */
/*   Updated: 2021/03/31 11:23:07 by ocarlos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <stdlib.h>
# include <math.h>
# include <stdint.h>
# include <errno.h>
# include <string.h>
# include <stdio.h>
# include "minilibx/mlx.h"
# include "gnl/get_next_line.h"

# define TRUE 1
# define FALSE 0
# define GAMESPEED 0.5
# define INIT_WALKSPD 16
# define INIT_TURNSPD 6
# define MOVESPEED 1
# define KEYPRESS 2
# define KEYRELEASE 3
# define MOUSECLICK 33
# define TEXTURE_COUNT 4
# define SPRITE_COUNT 1
# define UP 119
# define DOWN 115
# define RIGHT 100
# define LEFT 97
# define STRFR 101
# define STRFL 113
# define ESC 65307
# define PI 3.14159265
# define TILE_SIZE 64
# define MAP_SCALE 0.1
# define T_CL uint32_t

typedef struct	s_pos
{
	float		x;
	float		y;
}				t_pos;
typedef struct	s_size
{
	int			h;
	int			w;
}				t_size;
typedef struct	s_dir
{
	int			u;
	int			d;
	int			l;
	int			r;
	int			sl;
	int			sr;
}				t_dir;
typedef struct	s_img
{
	void		*img;
	char		*addr;
	int			bpp;
	int			ln_lngt;
	int			endian;
	t_size		size;
	t_pos		pos;
}				t_img;
typedef struct	s_txtr
{
	char		*path;
	t_img		instc;
	t_size		size;
	T_CL		*buffer;
}				t_txtr;
typedef struct	s_sprt
{
	float		dstnc;
	float		angle;
	int			visbl;
	t_txtr		txtr;
	t_pos		pos;
}				t_sprt;
typedef struct	s_player
{
	int			turndir;
	int			walkdir;
	int			strafe;
	float		rt_angl;
	float		walkspd;
	float		turnspd;
	t_img		spr;
}				t_player;
typedef struct	s_rays
{
	float		angle;
	float		dist;
	int			v_hit;
	int			fndwall;
	int			ctntwall;
	t_dir		face;
	t_pos		wallhit;
	t_pos		n_touch;
	t_img		rayspr;
}				t_rays;
typedef struct	s_file
{
	char		*txpath[TEXTURE_COUNT];
	char		*sppath[SPRITE_COUNT];
	char		plrdir;
	int			argcnt;
	int			bmp;
	int			*map;
	int			rgbup[3];
	int			rgbdw[3];
	t_pos		strtpos;
	t_size		scrsize;
	t_size		mapsize;
}				t_file;
typedef struct	s_data
{
	void		*mlx;
	void		*mlx_win;
	int			vsbspr[SPRITE_COUNT];
	int			*maptbl;
	int			c_clr;
	int			f_clr;
	int			n_rays;
	float		fov;
	float		dpp;
	float		gamespd;
	t_file		cub;
	t_sprt		spr[SPRITE_COUNT];
	t_txtr		txt[TEXTURE_COUNT];
	t_dir		dir;
	t_size		scrsz;
	t_size		mapsz;
	T_CL		*buf;
	t_img		tile;
	t_rays		*rays;
	t_player	plr;
}				t_data;
typedef struct	s_3dproj
{
	int			cltop;
	int			clbot;
	int			strph;
	int			i;
	int			y;
	float		pldist;
	float		prwallh;
}				t_3dproj;
typedef struct	s_pjspr
{
	int			x;
	int			y;
	int			xofst;
	int			yofst;
	int			dsttop;
	float		h;
	float		w;
	float		topy;
	float		btmy;
	float		angle;
	float		scrx;
	float		lftx;
	float		rgtx;
	float		txlw;
	T_CL		*buff;
	T_CL		color;
	t_size		texsz;
}				t_pjspr;
typedef struct	s_cnt
{
	int			x;
	int			y;
	int			i;
	int			j;
}				t_cnt;
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

int		ft_id_n_load(t_file *cubfile, char *line, int fd);
void	ft_load_cub_file(t_data *d, int argc, char **argv);
int		ft_init_win(t_data *d);
void	ft_init_img(t_data *d);
void	ft_init_map_size(t_data *d);
void	ft_init_player(t_data *d);
int		ft_init_sprite_struct(t_data *d);
int		ft_init_raytemp(t_rays *raytemp, float angle);
int		ft_clear_colorbuffer(t_data *d, int init);
void	ft_init_drwstruct(t_drwline *c, t_pos *i_pos, t_pos *f_pos);
void	ft_load_file_paths(t_data *d);
void	ft_load_xpm_texture(t_data *d);
void	ft_load_xpm_sprite(t_data *d);
int		ft_loadmap(t_data *d);
int		ft_loadcolors(t_data *d);
void	ft_setup(t_data *d);
int		ft_update(t_data *d);
int		ft_draw(t_data *d);
void	ft_destroy_images(t_data *d);
void	ft_destroy(t_data *d, int f);
int		ft_key_press(int keycode, t_data *d);
int		ft_key_release(int keycode, t_data *d);
int		ft_mouseclose(t_data *d);
void	ft_print_pixel(t_data *d, int x, int y, int color);
int		ft_drwln(t_data *d, t_pos i_pos, t_pos f_pos, int color, int resize);
int		ft_drwrt(t_data *d, t_pos pos, t_size size, int color, int resize);
void	ft_update_colorbuffer(t_data *d, t_pos pos, int color);
int		ft_print_colorbuffer(t_data *d);
float	ft_normalize_angle(float angle);
float	ft_normalize_angle2(float angle);
float	ft_sprite_arctan(t_data *d, int i);
float	ft_distance(t_pos coord_a, t_pos coord_b);
void	ft_reset_array(int *array, int i);
int		ft_pos(int w, int x, int y);
int		ft_invalid_screen_area(t_data *d, float x, float y);
int		ft_invalid_map_position(t_data *d, float x, float y);
int		ft_invalid_area(t_data *d, float x, float y);
int		ft_move_player(t_data *d);
int		ft_player_direction(t_data *d);
int		ft_fndwall(t_data *d, t_rays *rtmp, t_pos chk, t_pos step, int isvtc);
int		ft_h_intsc(t_data *d, t_rays *rtmp, t_pos icpt, t_pos step, float ang);
int		ft_v_intsc(t_data *d, t_rays *rtmp, t_pos icpt, t_pos step, float ang);
int		ft_fill_ray(t_data *d, t_rays *rtmp, int is_vert, int stp_id);
int		ft_cast_ray(t_data *d, float ang, int stp_id);
int		ft_cast_all_rays(t_data *d);
int		ft_project_texture(t_data *d, t_3dproj *projection, int tex_ind);
void	ft_walltext(t_data *d, t_3dproj *prj);
void	ft_gen_3d_proj(t_data *d);
int		ft_loopwall(t_data *d, t_rays *rtmp);
int		ft_wallhit(t_data *d, t_rays *rtmp, int mapcontent, t_cnt *corr);
void	ft_update_sprite(t_data *d);
void	ft_set_sprite(t_data *d, t_pjspr *sprite, int i);
void	ft_sprite_projection(t_data *d, t_pjspr *sprite, int i);
void	ft_draw_sprite(t_data *d);
int		ft_find_sprite(t_data *d);
void	ft_free_c_line(char **clean_line);
void	ft_ex_wrongdata(t_file *cubfile, char **clean_line, int fd);
void	ft_ex_wrongmap(t_file *cubfile, int f);
void	ft_error(void);
void	ft_validargs(t_file *cubfile, int argc, char **argv);
t_size ft_ck_scrsize(t_file *cubfile, char **clean_line, int fd);
int		ft_ck_fileext(char *line1, char *line2);
int		ft_ck_filetype(t_file *cubfile, char **clean_line, int fd);
void	ft_ck_rgbvalues(t_file *cubfile, char **clean_line, int *rgb, int fd);
int		ft_ck_mapdata(t_file *cubfile);
int		ft_ck_validchar(int *map, t_cnt c, t_file *cubfile);
int		ft_ck_sprite(t_file *cubfile, int *trgr);
void	ft_ck_validmap(t_file *cubfile);
void	ft_argtest(t_file *cubfile, char **clean_line, int fd);
int		ft_id_n_load(t_file *cubfile, char *line, int fd);
int		ft_testmapchar(char *line);
void	ft_getmapdata(t_file *cubfile, char *line, int fd);
void	ft_mapfill_1(t_file *cubfile, char *line, t_cnt *c);
void	ft_mapfill_2(t_file *cubfile, char *line, t_cnt *c);
void	ft_mapfill_3(t_file *cubfile, char *line, t_cnt *c);
void	ft_mapfill(t_file *cubfile, char *line, t_cnt *c);
void	ft_processmap(t_file *cubfile, char *line, int fd);
void	ft_load_cub_file(t_data *d, int argc, char **argv);
T_CL	ft_crt_trgb(int t, int r, int g, int b);
T_CL	ft_get_t(int trgb);
T_CL	ft_get_r(int trgb);
T_CL	ft_get_g(int trgb);
T_CL	ft_get_b(int trgb);
size_t	ft_strlen(const char *s);
void	*ft_memcpy(void *dest, const void *src, size_t n);
char	*ft_strdup(const char *s1);
char	**ft_setarray(char *temp, char ch);
int		*ft_setdelim(char *temp, char ch);
char	**ft_split(char const *s, char c);
int		ft_isdigit(int c);
int		ft_tstspc(const char ch);
int		ft_atoi(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strchr(const char *s, int c);
int		ft_isascii(int c);
void	*ft_bzero(void *s, size_t n);
void	ft_bitwiseconv(unsigned char *addr, unsigned int value);
void	ft_write_file(t_data *d, int fd);
void	ft_save_img(t_data *d);
#endif
