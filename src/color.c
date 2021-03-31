/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarlos- <ocarlos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 16:09:30 by ocarlos-          #+#    #+#             */
/*   Updated: 2021/03/30 17:07:00 by ocarlos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
** t_cl	ft_crt_trgb(int t, int r, int g, int b)
**      returns a color in hexadecimal format to use in minilibx
** t_cl	ft_get_t(int trgb)
**      gets a color in minilibx format and returns its transparency
** t_cl	ft_get_r(int trgb)
**      gets a color in minilibx format and returns its red value
** t_cl	ft_get_g(int trgb)
**      gets a color in minilibx format and returns its green value
** t_cl	ft_get_b(int trgb)
**      gets a color in minilibx format and returns its blue value
*/

t_cl	ft_crt_trgb(int t, int r, int g, int b)
{
	return(t << 24 | r << 16 | g << 8 | b);
}

t_cl	ft_get_t(int trgb)
{
	return (trgb & (0xFF << 24));
}

t_cl	ft_get_r(int trgb)
{
	return (trgb & (0xFF << 16));
}

t_cl	ft_get_g(int trgb)
{
	return (trgb & (0xFF << 8));
}

t_cl	ft_get_b(int trgb)
{
	return (trgb & 0xFF);
}
