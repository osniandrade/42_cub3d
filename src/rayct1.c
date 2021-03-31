/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rayct1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarlos- <ocarlos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 16:09:30 by ocarlos-          #+#    #+#             */
/*   Updated: 2021/03/31 11:37:31 by ocarlos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
** int	ft_fwl(t_data *d, t_rays *rtmp, t_pos chk, t_pos step, int isvtc)
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

int		ft_fwl(t_data *d, t_rays *rtmp, t_pos chk, t_pos st, int isvtc)
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
			rtmp->n_touch.x += st.x;
			rtmp->n_touch.y += st.y;
		}
	}
	return (TRUE);
}

int		ft_in_h(t_data *d, t_rays *rtmp, t_pos it, t_pos st, float ang)
{
	t_pos	toCheck;
	t_pos	p_pos;

	p_pos = d->plr.spr.pos;
	rtmp->wallhit.x = 0;
	rtmp->wallhit.y = 0;
	it.y = floor(p_pos.y / d->tile.size.w) * d->tile.size.w;
	it.y += rtmp->face.d ? d->tile.size.w : 0;
	it.x = p_pos.x + (it.y - p_pos.y) / tan(ang);
	st.y = d->tile.size.w;
	st.y *= rtmp->face.u ? -1 : 1;
	st.x = d->tile.size.w / tan(ang);
	st.x *= (rtmp->face.l && st.x > 0) ? -1 : 1;
	st.x *= (rtmp->face.r && st.x < 0) ? -1 : 1;
	rtmp->n_touch.x = it.x;
	rtmp->n_touch.y = it.y;
	ft_fwl(d, rtmp, toCheck, st, 0);
	return (TRUE);
}

int		ft_in_v(t_data *d, t_rays *rtmp, t_pos it, t_pos st, float ang)
{
	t_pos	toCheck;
	t_pos	p_pos;

	p_pos = d->plr.spr.pos;
	rtmp->wallhit.x = 0;
	rtmp->wallhit.y = 0;
	it.x = floor(p_pos.x / d->tile.size.w) * d->tile.size.w;
	it.x += rtmp->face.r ? d->tile.size.w : 0;
	it.y = p_pos.y + (it.x - p_pos.x) * tan(ang);
	st.x = d->tile.size.w;
	st.x *= rtmp->face.l ? -1 : 1;
	st.y = d->tile.size.w * tan(ang);
	st.y *= (rtmp->face.u && st.y > 0) ? -1 : 1;
	st.y *= (rtmp->face.d && st.y < 0) ? -1 : 1;
	rtmp->n_touch.x = it.x;
	rtmp->n_touch.y = it.y;
	ft_fwl(d, rtmp, toCheck, st, 1);
	return (TRUE);
}

int		ft_fill_ray(t_data *d, t_rays *rtmp, int isvtc, int stp_id)
{
	d->rays[stp_id].dist = ft_distance(d->plr.spr.pos, rtmp->wallhit);
	d->rays[stp_id].wallhit.x = rtmp->wallhit.x;
	d->rays[stp_id].wallhit.y = rtmp->wallhit.y;
	d->rays[stp_id].face.u = rtmp->face.u;
	d->rays[stp_id].face.d = rtmp->face.d;
	d->rays[stp_id].face.l = rtmp->face.l;
	d->rays[stp_id].face.r = rtmp->face.r;
	d->rays[stp_id].fndwall = rtmp->fndwall;
	d->rays[stp_id].ctntwall = rtmp->ctntwall;
	if (isvtc)
		d->rays[stp_id].v_hit = TRUE;
	else
		d->rays[stp_id].v_hit = FALSE;
	return (TRUE);
}

int		ft_cast_ray(t_data *d, float ang, int stp_id)
{
	t_rays	raytemp_h;
	t_rays	raytemp_v;
	t_pos	intercept;
	t_pos	step;
	t_pos	dist;

	ang = ft_normalize_angle(ang);
	ft_init_raytemp(&raytemp_h, ang);
	ft_init_raytemp(&raytemp_v, ang);
	ft_in_h(d, &raytemp_h, intercept, step, ang);
	ft_in_v(d, &raytemp_v, intercept, step, ang);
	dist.x = raytemp_h.fndwall ? ft_distance(d->plr.spr.pos, raytemp_h.wallhit) : __FLT_MAX__;
	dist.y = raytemp_v.fndwall ? ft_distance(d->plr.spr.pos, raytemp_v.wallhit) : __FLT_MAX__;
	if (dist.y < dist.x)
		ft_fill_ray(d, &raytemp_v, 1, stp_id);
	else
		ft_fill_ray(d, &raytemp_h, 0, stp_id);
	d->rays[stp_id].angle = ang;
	return (TRUE);
}
