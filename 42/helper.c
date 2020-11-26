/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarlos- <ocarlos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 09:29:52 by ocarlos-          #+#    #+#             */
/*   Updated: 2020/11/26 10:03:59 by ocarlos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "constants.c"

typedef struct	s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int 	endian;
	int 	color;
} 			t_data;

// creates a buffer to renderize before writing a image to screen
// rendering offset included to garantee the draw is within the window limits
void	ft_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + ((y * data->line_length) + (x * (data->bits_per_pixel / 8)));
	*(unsigned int *)dst = color;
}

// draw basic shapes
// 1 = square
int		ft_drawbasicshape(t_data *data, int x, int y, int shape, int size)
{
	int newx;
	int newy;

	newx = x;
	newy = y;
	if (shape = 1)
	{
		while (newx++ < size)
		{
			while (newy++ < size)
				ft_mlx_pixel_put(data, newx, newy, data->color);
			newy = y;
		}
		return (TRUE);
	}
	return (FALSE);
}