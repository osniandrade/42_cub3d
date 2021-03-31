/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarlos- <ocarlos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 15:49:54 by ocarlos-          #+#    #+#             */
/*   Updated: 2021/03/30 16:59:21 by ocarlos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
** void	ft_bitwiseconv(unsigned char *addr, unsigned int value)
**		does the bitwise conversion of some header info
** void	ft_write_file(t_data *d, int fd)
**		writes the header info and the color buffer into the file
** void	ft_save_img(t_data *d)
**		opens the save.bmp file, closes it and finishes the program
*/

void	ft_bitwiseconv(unsigned char *addr, unsigned int value)
{
	addr[0] = (unsigned char)(value);
	addr[1] = (unsigned char)(value >> 8);
	addr[2] = (unsigned char)(value >> 16);
	addr[3] = (unsigned char)(value >> 24);
}

void	ft_write_file(t_data *d, int fd)
{
	unsigned char	file[54];
	int				filesize;
	t_cnt			c;
	t_cl		color;

	c.y = 0;
	c.i = d->scrsz.w;
	c.j = d->scrsz.h;
	c.x = c.i * c.j;
	ft_bzero(&file, 54);
	filesize = 54 + (c.i * c.j);
	file[0] = (unsigned char)('B');
	file[1] = (unsigned char)('M');
	ft_bitwiseconv(&file[2], filesize);
	file[10] = (unsigned char)(54);
	file[14] = (unsigned char)(40);
	ft_bitwiseconv(&file[18], c.i);
	ft_bitwiseconv(&file[22], -c.j);
	file[26] = (unsigned char)(1);
	file[28] = (unsigned char)(32);
	write(fd, &file, 54);
	while (c.y < c.x)
	{
		color = (t_cl)(d->buf[c.y++]);
		write(fd, &color, 4);
	}
}

void	ft_save_img(t_data *d)
{
    int	fd;

    fd = open("save.bmp", O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, 777);
	ft_write_file(d, fd);
	close(fd);
	ft_destroy(d, 1);
}