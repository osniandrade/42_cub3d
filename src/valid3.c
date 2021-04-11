/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarlos- <ocarlos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 16:09:30 by ocarlos-          #+#    #+#             */
/*   Updated: 2021/04/11 10:24:14 by ocarlos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
** void	ft_ck_startpos(t_file *file)
**		checks if there is a player start position
*/

void	ft_ck_startpos(t_file *file)
{
	if (file->strtpos.x == 0 || file->strtpos.y == 0)
	{
		printf("missing player start position\n");
		ft_ex_wrongmap(file, 1);
	}
}
