/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarlos- <ocarlos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 16:09:30 by ocarlos-          #+#    #+#             */
/*   Updated: 2021/04/10 15:11:36 by ocarlos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
**  void	ft_sortspr(t_data *d)
**          sorts thesprites in order from fartest to closest
*/

void	ft_sortspr(t_data *d)
{
	int		i;
	t_sprt	temp;

	i = d->n_spr - 1;
	while (i > 0)
	{
		if (d->spr[i].dstnc > d->spr[i - 1].dstnc)
		{
			temp = d->spr[i];
			d->spr[i] = d->spr[i - 1];
			d->spr[i - 1] = temp;
			i = d->n_spr;
		}
		i--;
	}
}
