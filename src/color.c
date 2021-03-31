/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarlos- <ocarlos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 16:09:30 by ocarlos-          #+#    #+#             */
/*   Updated: 2021/03/31 11:06:29 by ocarlos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
** T_CL	ft_crt_trgb(int t, int r, int g, int b)
**      returns a color in hexadecimal format to use in minilibx
** T_CL	ft_get_t(int trgb)
**      gets a color in minilibx format and returns its transparency
** T_CL	ft_get_r(int trgb)
**      gets a color in minilibx format and returns its red value
** T_CL	ft_get_g(int trgb)
**      gets a color in minilibx format and returns its green value
** T_CL	ft_get_b(int trgb)
**      gets a color in minilibx format and returns its blue value
*/

T_CL	ft_crt_trgb(int t, int r, int g, int b)
{
	return(t << 24 | r << 16 | g << 8 | b);
}

T_CL	ft_get_t(int trgb)
{
	return (trgb & (0xFF << 24));
}

T_CL	ft_get_r(int trgb)
{
	return (trgb & (0xFF << 16));
}

T_CL	ft_get_g(int trgb)
{
	return (trgb & (0xFF << 8));
}

T_CL	ft_get_b(int trgb)
{
	return (trgb & 0xFF);
}
