/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarlos- <ocarlos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 13:44:25 by ocarlos-          #+#    #+#             */
/*   Updated: 2021/03/05 17:53:46 by ocarlos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


// gives sprite a fixed random position
int		ft_test_init_sprite(t_data *data)
{
	data->sprite[0].pos.x = (SCREENH / 2) + 200;
	data->sprite[0].pos.y = (SCREENW / 2);

	return (TRUE);
}