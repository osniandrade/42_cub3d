/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarlos- <ocarlos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 13:44:25 by ocarlos-          #+#    #+#             */
/*   Updated: 2021/03/20 15:47:31 by ocarlos-         ###   ########.fr       */
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
void	ft_t_printmap(t_filedata *cubfile)
{
	t_count c;

	c = (t_count) {0};
	c.i = cubfile->mapsize.w;
	c.j = cubfile->mapsize.h;
	while (c.y < c.j)
	{
		c.x = 0;
		while (c.x < c.i)
		{
			printf("%d, ", cubfile->map[ft_pos(c.i, c.x, c.y)]);
			c.x++;
		}
		printf("\n");
		c.y++;
	}
}