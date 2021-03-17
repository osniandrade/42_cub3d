/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarlos- <ocarlos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 13:44:25 by ocarlos-          #+#    #+#             */
/*   Updated: 2021/03/17 10:23:44 by ocarlos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


// gives sprite a fixed random position
int		ft_test_init_sprite(t_data *data)
{
	data->sprites[0].pos.x = (data->screensize.h / 2) + 200;
	data->sprites[0].pos.y = (data->screensize.w / 2);

	return (TRUE);
}

// prints map on data structure
void	ft_t_printmap(t_data *data)
{
	int x = 0;
	int y = 0;

	while (y < data->mapsize.h)
	{
		x = 0;
		while (x < data->mapsize.w)
		{
			printf("%d, ", data->maptable[(data->mapsize.w * y) + x]);
			x++;
		}
		printf("\n");
		y++;
	}
}