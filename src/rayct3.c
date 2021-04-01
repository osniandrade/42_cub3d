/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rayct3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarlos- <ocarlos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 16:09:30 by ocarlos-          #+#    #+#             */
/*   Updated: 2021/03/31 11:50:39 by ocarlos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
** int	ft_loopwall(t_data *d, t_rays *rtmp)
**		checks if wall is found and in the field of view
** int	ft_wallhit(t_data *d, t_rays *rtmp, int mapcontent, t_cnt *corr)
**		if wall is found, fills the rtmp array
*/

int		ft_loopwall(t_data *d, t_rays *rtmp)
{
	if (rtmp->n_touch.x >= 0 && 
		floor(rtmp->n_touch.x / d->tile.size.w) <= d->mapsz.w && 
		rtmp->n_touch.y > 0 && 
		floor(rtmp->n_touch.y / d->tile.size.w) <= d->mapsz.h)
		return (TRUE);
	else
		return (FALSE);
}

int		ft_wallhit(t_data *d, t_rays *rtmp, int mapct, t_cnt *corr)
{
	if (ft_invalid_map_position(d, corr->x, corr->y) && (mapct == 1))
	{
		rtmp->w_hit.x = rtmp->n_touch.x;
		rtmp->w_hit.y = rtmp->n_touch.y;
		rtmp->ctntwall = mapct;
		rtmp->fndwall = TRUE;
		return (TRUE);
	}
	else
	return (FALSE);
}