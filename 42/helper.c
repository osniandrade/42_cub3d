/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarlos- <ocarlos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 09:29:52 by ocarlos-          #+#    #+#             */
/*   Updated: 2020/12/02 15:10:29 by ocarlos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// returns a color in hexadecimal format to use in minilibx
int		ft_crt_trgb(int t, int r, int g, int b)
{
	return(t << 24 | r << 16 | g << 8 | b);
}

// gets a color in minilibx format and returns its transparency
int		ft_get_t(int trgb)
{
	return (trgb & (0xFF << 24));
}

// gets a color in minilibx format and returns its red value
int		ft_get_r(int trgb)
{
	return (trgb & (0xFF << 16));
}

// gets a color in minilibx format and returns its green value
int		ft_get_g(int trgb)
{
	return (trgb & (0xFF << 8));
}

// gets a color in minilibx format and returns its blue value
int		ft_get_b(int trgb)
{
	return (trgb & 0xFF);
}
