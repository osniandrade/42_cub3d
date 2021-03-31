/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rayct1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarlos- <ocarlos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 16:09:30 by ocarlos-          #+#    #+#             */
/*   Updated: 2021/03/30 16:44:09 by ocarlos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
** int	ft_fndwall(t_data *d, t_rays *rtmp, t_pos chk, t_pos step, int isvtc)
**		loops until a wall is found - 
** 		0 for horizontal check
**		1 for vertical check
** int	ft_h_intsc(t_data *d, t_rays *rtmp, t_pos icpt, t_pos step, float ang)
**		calculates horizontal ray intersection on the grid
** int	ft_v_intsc(t_data *d, t_rays *rtmp, t_pos icpt, t_pos step, float ang)
**		calculates vertical ray intersection on the grid
** int	ft_fill_ray(t_data *d, t_rays *rtmp, int isvtc, int stripId)
**		copies the values from raytemp to actual ray struct array position
** int	ft_cast_ray(t_data *d, float ang, int stripId)
**		function responsible for casting each ray
*/

int		ft_fndwall(t_data *d, t_rays *rtmp, t_pos chk, t_pos step, int isvtc)
{
	int		mapcontent;
	t_cnt	corr;

	corr.i = d->mapsz.w;
	while (ft_loopwall(d, rtmp))
	{
		chk.x = rtmp->n_touch.x;
		chk.y = rtmp->n_touch.y;
		if (isvtc)
			chk.x += (rtmp->face.l ? -1 : 0);
		else
			chk.y += (rtmp->face.u ? -1 : 0);
		corr.x = (int)floor(chk.x / d->tile.size.w);
		corr.y = (int)floor(chk.y / d->tile.size.w);
		if (corr.x < d->mapsz.w && corr.y < d->mapsz.h)
			mapcontent = d->maptbl[ft_pos(corr.i, corr.x, corr.y)];
		if (ft_wallhit(d, rtmp, mapcontent, &corr))
			break;
		else
		{
			rtmp->n_touch.x += step.x;
			rtmp->n_touch.y += step.y;
		}
	}
	return (TRUE);
}

int		ft_h_intsc(t_data *d, t_rays *rtmp, t_pos icpt, t_pos step, float ang)
{
	t_pos	toCheck;
	t_pos	p_pos;

	p_pos = d->plr.spr.pos;
	rtmp->wallhit.x = 0;
	rtmp->wallhit.y = 0;
	icpt.y = floor(p_pos.y / d->tile.size.w) * d->tile.size.w;
	icpt.y += rtmp->face.d ? d->tile.size.w : 0;
	icpt.x = p_pos.x + (icpt.y - p_pos.y) / tan(ang);
	step.y = d->tile.size.w;
	step.y *= rtmp->face.u ? -1 : 1;
	step.x = d->tile.size.w / tan(ang);
	step.x *= (rtmp->face.l && step.x > 0) ? -1 : 1;
	step.x *= (rtmp->face.r && step.x < 0) ? -1 : 1;
	rtmp->n_touch.x = icpt.x;
	rtmp->n_touch.y = icpt.y;
	ft_fndwall(d, rtmp, toCheck, step, 0);
	return (TRUE);
}

int		ft_v_intsc(t_data *d, t_rays *rtmp, t_pos icpt, t_pos step, float ang)
{
	t_pos	toCheck;
	t_pos	p_pos;

	p_pos = d->plr.spr.pos;
	rtmp->wallhit.x = 0;
	rtmp->wallhit.y = 0;
	icpt.x = floor(p_pos.x / d->tile.size.w) * d->tile.size.w;
	icpt.x += rtmp->face.r ? d->tile.size.w : 0;
	icpt.y = p_pos.y + (icpt.x - p_pos.x) * tan(ang);
	step.x = d->tile.size.w;
	step.x *= rtmp->face.l ? -1 : 1;
	step.y = d->tile.size.w * tan(ang);
	step.y *= (rtmp->face.u && step.y > 0) ? -1 : 1;
	step.y *= (rtmp->face.d && step.y < 0) ? -1 : 1;
	rtmp->n_touch.x = icpt.x;
	rtmp->n_touch.y = icpt.y;
	ft_fndwall(d, rtmp, toCheck, step, 1);
	return (TRUE);
}

int		ft_fill_ray(t_data *d, t_rays *rtmp, int isvtc, int stripId)
{
	d->rays[stripId].dist = ft_distance(d->plr.spr.pos, rtmp->wallhit);
	d->rays[stripId].wallhit.x = rtmp->wallhit.x;
	d->rays[stripId].wallhit.y = rtmp->wallhit.y;
	d->rays[stripId].face.u = rtmp->face.u;
	d->rays[stripId].face.d = rtmp->face.d;
	d->rays[stripId].face.l = rtmp->face.l;
	d->rays[stripId].face.r = rtmp->face.r;
	d->rays[stripId].fndwall = rtmp->fndwall;
	d->rays[stripId].ctntwall = rtmp->ctntwall;
	if (isvtc)
		d->rays[stripId].v_hit = TRUE;
	else
		d->rays[stripId].v_hit = FALSE;
	return (TRUE);
}

int		ft_cast_ray(t_data *d, float ang, int stripId)
{
	t_rays	raytemp_h;
	t_rays	raytemp_v;
	t_pos	intercept;
	t_pos	step;
	t_pos	dist;

	ang = ft_normalize_angle(ang);
	ft_init_raytemp(&raytemp_h, ang);
	ft_init_raytemp(&raytemp_v, ang);
	ft_h_intsc(d, &raytemp_h, intercept, step, ang);
	ft_v_intsc(d, &raytemp_v, intercept, step, ang);
	dist.x = raytemp_h.fndwall ? ft_distance(d->plr.spr.pos, raytemp_h.wallhit) : __FLT_MAX__;
	dist.y = raytemp_v.fndwall ? ft_distance(d->plr.spr.pos, raytemp_v.wallhit) : __FLT_MAX__;
	if (dist.y < dist.x)
		ft_fill_ray(d, &raytemp_v, 1, stripId);
	else
		ft_fill_ray(d, &raytemp_h, 0, stripId);
	d->rays[stripId].angle = ang;
	return (TRUE);
}
