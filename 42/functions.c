/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarlos- <ocarlos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 16:09:30 by ocarlos-          #+#    #+#             */
/*   Updated: 2020/11/26 09:52:59 by ocarlos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "constants.c"

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

// tests a system and returns true if it is little endian
// CHECK IF REALLY NEEDED
int		ft_lt_endian()
{
	unsigned int	i;

	i = 1;
	char *c = (char *)&i;
	if (*c)
		return (TRUE);
	else
		return (FALSE);
}
