/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarlos- <ocarlos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 16:09:30 by ocarlos-          #+#    #+#             */
/*   Updated: 2021/04/01 17:29:18 by ocarlos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
** int	ft_init_sprite_struct(t_data *d)
**		initializes sprite structs with zero
** int	ft_init_raytemp(t_rays *raytemp, float rayAngle)
**		initializes raytemp struct with basic values
** int	ft_clear_colorbuffer(t_data *d, int init)
**		initializes the colorbuffer
**		init = 0 - skips memory allocation
**		init = 1 - allocates memory for buffer
** void	ft_init_drwstruct(t_drwline *c, t_coord *i_pos, t_coord *f_pos)
**		inits ft_draw_line struct values
** void	ft_initsprproj(t_data *d, t_pjspr *spr, int i)
**		fills sprite info for projection calculation
*/

// int		ft_init_sprite_struct(t_data *d)
// {
// 	int		i;

// 	i = 0;
// 	while (i < SPRITE_COUNT)
// 		d->spr[i++] = (t_sprt) {0};
// 	return (TRUE);
// }

// int		ft_init_raytemp(t_rays *raytemp, float angle)
// {
// 	*raytemp = (t_rays) {0};
// 	raytemp->face.d = (angle > 0 && angle < PI);
// 	raytemp->face.u = !(raytemp->face.d);
// 	raytemp->face.r = (angle < (0.5 * PI) || angle > (1.5 * PI));
// 	raytemp->face.l = !(raytemp->face.r);
// 	raytemp->t_ang = angle;
// 	return (TRUE);
// }

int		ft_clear_colorbuffer(t_data *d, int init)
{
	int		i;

	i = 0;
	if(init == 1)
		d->buf = (T_CL *)malloc(sizeof(T_CL) * (T_CL)d->scrsz.w * (T_CL)d->scrsz.h);
	while(i < d->scrsz.w * d->scrsz.h)
		d->buf[i++] = ft_crt_trgb(255, 0, 0, 0);
	return (TRUE);
}

void	ft_init_drwstruct(t_drwline *c, t_pos *i_pos, t_pos *f_pos)
{
	c->i_x = round(i_pos->x);
	c->i_y = round(i_pos->y);
	c->f_x = round(f_pos->x);
	c->f_y = round(f_pos->y);
	c->dx = abs((int)c->f_x - (int)c->i_x);
	c->sx = c->i_x < c->f_x ? 1 : -1;
	c->dy = abs((int)c->f_y - (int)c->i_y);
	c->sy = c->i_y < c->f_y ? 1 : -1;
	c->err = (c->dx > c->dy ? c->dx : -c->dy) / 2;
}

void	ft_initsprproj(t_data *d, t_pjspr *spr, int i)
{
	spr->dsttop = spr->y + (spr->h / 2) - (d->scrsz.h / 2);
	spr->yofst = spr->dsttop * (spr->texsz.h / spr->h);
	spr->buff = (T_CL*)d->spr[i].txtr.buffer;
	spr->t_pos = ft_pos(spr->texsz.w, spr->xofst, spr->yofst);
	spr->color = spr->buff[spr->t_pos];
	spr->t_pos = ft_pos(d->scrsz.w, spr->x, spr->y);
}
