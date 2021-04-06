/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarlos- <ocarlos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 16:09:30 by ocarlos-          #+#    #+#             */
/*   Updated: 2021/04/06 19:57:04 by ocarlos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
** void	ft_mapfill_2(t_file *file, char *line, t_cnt *c)
**		checks map position for player start position
** void	ft_mapfill_3(t_file *file, char *line, t_cnt *c)
**		checks map position for wall, walk area or sprite positions
** void	ft_mapfill(t_file *file, char *line, t_cnt *c)
**		tests for the character and fills the struct array
** void	ft_processmap(t_file *file, char *line, int fd)
**		fills the map array with the .cub file info
** void	ft_load_cub_file(t_data *d, int argc, char **argv)
**		loads the .cub file into the struct
*/

void	ft_mapfill_2(t_file *file, char *line, t_cnt *c)
{
	if (line[c->x] == 'N' || line[c->x] == 'S' ||
		line[c->x] == 'W' || line[c->x] == 'E')
	{
		file->map[(file->mapsize.w * c->y) + c->i] = 0;
		if (file->plrdir == '0')
			file->plrdir = line[c->x];
		else
		{
			printf("invalid player start position\n");
			ft_ex_wrongmap(file, 1);
		}
		file->strtpos.x = c->x * TILE_SIZE;
		file->strtpos.y = c->y * TILE_SIZE;
	}
}

void	ft_mapfill_3(t_file *file, char *line, t_cnt *c)
{
	if (line[c->x] == '0' || line[c->x] == '1' || line[c->x] == '2')
		file->map[ft_pos(c->j, c->i, c->y)] = line[c->x] - 48;
}

void	ft_mapfill(t_file *file, char *line, t_cnt *c)
{
	if (line[c->x])
	{
		ft_mapfill_1(file, line, c);
		ft_mapfill_2(file, line, c);
		ft_mapfill_3(file, line, c);
		c->x++;
	}
	else
		file->map[ft_pos(c->j, c->i, c->y)] = 9;
	c->i++;
}

void	ft_processmap(t_file *file, char *line, int fd)
{
	t_cnt	c;

	c = (t_cnt) {0};
	c.j = file->mapsize.w;
	file->plrdir = '0';
	file->map = malloc(sizeof(int) * file->mapsize.h * file->mapsize.w);
	while (get_next_line(fd, &line))
	{
		if (ft_testmapchar(line))
		{
			while (c.i < file->mapsize.w)
				ft_mapfill(file, line, &c);
			c.i = 0;
			c.x = 0;
			c.y++;
		}
		free(line);
	}
	if (ft_testmapchar(line))
		while (c.i < file->mapsize.w)
			ft_mapfill(file, line, &c);
	free(line);
}

void	ft_load_cub_file(t_data *d, int argc, char **argv)
{
	t_file	file;
	int		fd;
	char	*line;

	errno = 0;
	file = (t_file) {0};
	ft_validargs(&file, argc, argv);
	fd = open(argv[1], O_RDONLY);
	ft_error();
	line = NULL;
	ft_id_n_load(&file, line, fd);
	ft_getmapdata(&file, line, fd);
	close(fd);
	ft_ck_mapdata(&file);
	fd = open(argv[1], O_RDONLY);
	line = NULL;
	ft_processmap(&file, line, fd);
	close(fd);
	ft_ck_validmap(&file);
	d->cub = file;
}
