/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarlos- <ocarlos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 13:44:25 by ocarlos-          #+#    #+#             */
/*   Updated: 2021/03/13 16:14:59 by ocarlos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


// gives sprite a fixed random position
int		ft_test_init_sprite(t_data *data)
{
	data->sprites[0].pos.x = (SCREENH / 2) + 200;
	data->sprites[0].pos.y = (SCREENW / 2);

	return (TRUE);
}

// prints map on data structure
void	ft_t_printmap(t_data *data)
{
	int x = 0;
	int y = 0;

	while (y < MAP_ROWS)
	{
		x = 0;
		while (x < MAP_COLS)
		{
			printf("%d, ", data->maptable[(data->mapsize.w * y) + x]);
			x++;
		}
		printf("\n");
		y++;
	}
}