/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarlos- <ocarlos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 16:09:30 by ocarlos-          #+#    #+#             */
/*   Updated: 2021/03/31 10:45:23 by ocarlos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
** void	ft_mapfill_2(t_file *cubfile, char *line, t_cnt *c)
**		checks map position for player start position
** void	ft_mapfill_3(t_file *cubfile, char *line, t_cnt *c)
**		checks map position for wall, walk area or sprite positions
** void	ft_mapfill(t_file *cubfile, char *line, t_cnt *c)
**		tests for the character and fills the struct array
** void	ft_processmap(t_file *cubfile, char *line, int fd)
**		fills the map array with the .cub file info
** void	ft_load_cub_file(t_data *d, int argc, char **argv)
**		loads the .cub file into the struct
*/

void	ft_mapfill_2(t_file *cubfile, char *line, t_cnt *c)
{
	if (line[c->x] == 'N' || line[c->x] == 'S' || 
		line[c->x] == 'W' || line[c->x] == 'E')
	{
		cubfile->map[(cubfile->mapsize.w * c->y) + c->i] = 0;
		if (cubfile->plrdir == '0')
			cubfile->plrdir = line[c->x];
		else
		{
			printf("invalid player start position\n");
			ft_ex_wrongmap(cubfile, 1);
		}
		cubfile->strtpos.x = c->x * TILE_SIZE;
		cubfile->strtpos.y = c->y * TILE_SIZE;
	}
}

void	ft_mapfill_3(t_file *cubfile, char *line, t_cnt *c)
{
	if (line[c->x] == '0' || line[c->x] == '1' || line[c->x] == '2')
		cubfile->map[ft_pos(c->j, c->i, c->y)] = line[c->x] - 48;
}

void	ft_mapfill(t_file *cubfile, char *line, t_cnt *c)
{
	if (line[c->x])
	{
		ft_mapfill_1(cubfile, line, c);
		ft_mapfill_2(cubfile, line, c);
		ft_mapfill_3(cubfile, line, c);
		c->x++;
	}
	else
		cubfile->map[ft_pos(c->j, c->i, c->y)] = 9;
	c->i++;
}

void	ft_processmap(t_file *cubfile, char *line, int fd)
{
	t_cnt	c;

	c = (t_cnt) {0};
	c.j = cubfile->mapsize.w;
	cubfile->plrdir = '0';
	cubfile->map = malloc(sizeof(int) * cubfile->mapsize.h * cubfile->mapsize.w);
	while (get_next_line(fd, &line))
	{
		if (ft_testmapchar(line))
		{
			while (c.i < cubfile->mapsize.w)
				ft_mapfill(cubfile, line, &c);
			c.i = 0;
			c.x = 0;
			c.y++;
		}
		free(line);
	}
	if (ft_testmapchar(line))
		while (c.i < cubfile->mapsize.w)
			ft_mapfill(cubfile, line, &c);
	free(line);
}

void	ft_load_cub_file(t_data *d, int argc, char **argv)
{
	t_file	cubfile;
	int		fd;
	char	*line;

	errno = 0;
	cubfile = (t_file) {0};
	ft_validargs(&cubfile, argc, argv);
	fd = open(argv[1], O_RDONLY);
	ft_error();
	line = NULL;
	ft_id_n_load(&cubfile, line, fd);
	ft_getmapdata(&cubfile, line, fd);
	close(fd);
	ft_ck_mapdata(&cubfile);
	fd = open(argv[1], O_RDONLY);
	line = NULL;
	ft_processmap(&cubfile, line, fd);
	close(fd);
	ft_ck_validmap(&cubfile);
	d->cub = cubfile;
}