/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keybrd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarlos- <ocarlos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 16:09:30 by ocarlos-          #+#    #+#             */
/*   Updated: 2021/03/30 15:30:45 by ocarlos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
** int	ft_key_press(int keycode, t_data *d)
**		changes key status to pressed and destroys window if pressed ESC
** int	ft_key_release(int keycode, t_data *d)
**		changes key status to not pressed
** int	ft_mouseclose(t_data *d)
**		execute when the x in windows is clicked
*/

int		ft_key_press(int keycode, t_data *d)
{
	if (keycode == ESC)
		ft_destroy(d, 1);
	if (keycode == LEFT)
		d->dir.l = TRUE;
	if (keycode == RIGHT)
		d->dir.r = TRUE;
	if (keycode == UP)
		d->dir.u = TRUE;
	if (keycode == DOWN)
		d->dir.d = TRUE;
	if (keycode == STRFL)
		d->dir.sl = TRUE;
	if (keycode == STRFR)
		d->dir.sr = TRUE;
	return (TRUE);
}

int		ft_key_release(int keycode, t_data *d)
{
	if (keycode == LEFT)
		d->dir.l = FALSE;
	if (keycode == RIGHT)
		d->dir.r = FALSE;
	if (keycode == UP)
		d->dir.u = FALSE;
	if (keycode == DOWN)
		d->dir.d = FALSE;
	if (keycode == STRFL)
	{
		d->dir.sl = FALSE;
		d->plr.strafe = FALSE;
	}
	if (keycode == STRFR)
	{
		d->dir.sr = FALSE;
		d->plr.strafe = FALSE;
	}
	return (TRUE);
}

int		ft_mouseclose(t_data *d)
{
	ft_destroy(d, 1);
	return (TRUE);
}