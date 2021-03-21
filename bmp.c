/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarlos- <ocarlos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 15:49:54 by ocarlos-          #+#    #+#             */
/*   Updated: 2021/03/21 18:15:12 by ocarlos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*******************************************************************************
 * BMP FILE CREATION
 *******************************************************************************/

int		ft_write_file(t_data *data, int file)
{
	t_bmpfilehead	fh;
	t_bmpfileinfo	fi;
	int				i;
	uint32_t		color;

	fh.type = 0x4d;
	fh.reserved1 = 0;
	fh.reserved2 = 0;
	fh.size = 2 + sizeof(t_bmpfilehead) + sizeof(t_bmpfileinfo) + (data->screensize.h * data->screensize.w * sizeof(uint32_t));
	fh.off_bits = 0x36;
	fi.size = sizeof(t_bmpfileinfo);
	fi.width = data->screensize.w;
	fi.height = data->screensize.h;
	fi.planes = 1;
	fi.bit_count = 32;
	fi.compression = 0;
	fi.size_image = 0;
	fi.x_pels_per_meter = 5000;
	fi.y_pels_per_meter = 5000;
	fi.clr_used = 0;
	fi.clr_important = 0;
	write(file, &fh, sizeof(fh));
	write(file, &fi, sizeof(fi));
	i = 0;
	while (i < data->screensize.w * data->screensize.h)
	{
		color = data->colorBuffer[i];
		write(file, &color, sizeof(uint32_t));
		i++;
	}
	return (TRUE);
}

void     ft_save_img(t_data *data)
{
    int	file;

    file = open("save.bmp", O_CREAT | O_RDWR | O_TRUNC, 0666);
	ft_write_file(data, file);
	close(file);
	ft_destroy(data, 1);
}