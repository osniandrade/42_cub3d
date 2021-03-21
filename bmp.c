/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarlos- <ocarlos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 15:49:54 by ocarlos-          #+#    #+#             */
/*   Updated: 2021/03/21 16:23:53 by ocarlos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*******************************************************************************
 * BMP FILE CREATION
 *******************************************************************************/

int		ft_write_file(t_data *data, int file)
{
	
}

int     ft_save_img(t_data *data)
{
    int	file;

    file = open("save.bmp", O_CREAT | O_RDWR | O_TRUNC, 0666);
	ft_write_file(data, file);
	close(file);
	ft_destroy(data, 1);
	return (TRUE);
}