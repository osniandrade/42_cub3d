/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rayct2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarlos- <ocarlos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 16:09:30 by ocarlos-          #+#    #+#             */
/*   Updated: 2021/03/31 11:30:30 by ocarlos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
** int	ft_cast_all_rays(t_data *d)
**		loop through all rays and fill the ray struct array
** int	ft_project_texture(t_data *d, t_3dproj *prj, int tex_ind)
**		projects the wall textures to each strip of each wall
** void	ft_walltext(t_data *d, t_3dproj *prj)
**		selects the wall texture based on facing direction
** void	ft_gen_3d_proj(t_data *d)
**		generates the 3D projection using raycasting
*/

int		ft_cast_all_rays(t_data *d)
{
	float	rayAngle;
	int		stripId;

	stripId = 0;
	rayAngle = d->plr.rt_angl + atan((stripId - (d->n_rays / 2)) / d->dpp);
	while (stripId < d->n_rays)
	{
		ft_cast_ray(d, rayAngle, stripId);
		rayAngle += d->fov / d->n_rays;
		rayAngle = ft_normalize_angle(rayAngle);
		stripId++;
	}
	return (TRUE);
}

int		ft_proj_txtr(t_data *d, t_3dproj *prj, int tex_ind)
{
	t_cnt	offset;
	int		dst_top;
	int		pos1;
	int		pos2;

	offset.i = d->scrsz.w;
	offset.j = d->txt[tex_ind].size.w;
	if (d->rays[prj->i].v_hit)
		offset.x = (int)d->rays[prj->i].wallhit.y % d->tile.size.w;
	else
		offset.x = (int)d->rays[prj->i].wallhit.x % d->tile.size.w;
	while (prj->y < prj->clbot)
	{
		dst_top = (prj->y + (prj->strph / 2) - (d->scrsz.h / 2));
		dst_top = (dst_top < 1) ? dst_top * -1 : dst_top;
		offset.y = dst_top * ((float)d->txt[tex_ind].size.h / prj->strph);
		pos1 = ft_pos(offset.i, prj->i, prj->y);
		pos2 = ft_pos(offset.j, offset.x, offset.y);
		d->buf[pos1] = (T_CL)d->txt[tex_ind].buffer[pos2];
		prj->y++;
	}
	return (TRUE);
}

void	ft_walltext(t_data *d, t_3dproj *prj)
{
	if (d->rays[prj->i].v_hit)
		if (d->rays[prj->i].face.l)
			ft_proj_txtr(d, prj, 0);
		else
			ft_proj_txtr(d, prj, 1);
	else
		if (d->rays[prj->i].face.u)
			ft_proj_txtr(d, prj, 2);
		else
			ft_proj_txtr(d, prj, 3);
}

void	ft_gen_3d_proj(t_data *d)
{
	t_3dproj	prj;
	float		c_res;

	prj.i = 0;
	while (prj.i < d->n_rays)
	{
		prj.y = 0;
		c_res = cos(d->rays[prj.i].angle - d->plr.rt_angl);
		prj.pldist = d->rays[prj.i].dist * c_res;
		prj.prwallh = (d->tile.size.w / prj.pldist) * d->dpp;
		prj.strph = (int)prj.prwallh;
		prj.cltop = (d->scrsz.h / 2) - (floor(prj.prwallh) / 2);
		prj.cltop = prj.cltop < 0 ? 0 : prj.cltop;
		prj.clbot = (d->scrsz.h / 2) + (prj.prwallh / 2);
		prj.clbot = prj.clbot > d->scrsz.h ? d->scrsz.h : prj.clbot;
		while (prj.y < prj.cltop)
			d->buf[(d->scrsz.w * prj.y++) + prj.i] = d->c_clr;
		ft_walltext(d, &prj);
		while (prj.y < d->scrsz.h)
			d->buf[ft_pos(d->scrsz.w, prj.i, prj.y++)] = d->f_clr;
		prj.i++;
	}
}
