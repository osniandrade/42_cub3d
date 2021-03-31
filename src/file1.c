/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarlos- <ocarlos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 16:09:30 by ocarlos-          #+#    #+#             */
/*   Updated: 2021/03/31 11:37:56 by ocarlos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
** void	ft_argtest(t_file *cubfile, char **clean_line, int fd)
**		tests for every argument in the .cub file
** int	ft_id_n_load(t_file *cubfile, char *line, int fd)
**		identifies the type of data and load into defined fields
** int	ft_testmapchar(char *line)
**		tests if the first valid char of a line is '1'
** void	ft_getmapdata(t_file *cubfile, char *line, int fd)
**		loads the size of the map
** void	ft_mapfill_1(t_file *cubfile, char *line, t_cnt *c)
**		checks map position for empty spaces (' ')
*/

void	ft_argtest(t_file *cubfile, char **clean_line, int fd)
{
	if (!ft_strncmp(clean_line[0], "R", 3))
		cubfile->scrsize = ft_ck_scrsize(cubfile, clean_line, fd);
	if (!ft_strncmp(clean_line[0], "NO", 3))
		if (ft_ck_filetype(cubfile, clean_line, fd))
			cubfile->txpath[0] = ft_strdup(clean_line[1]);
	if (!ft_strncmp(clean_line[0], "SO", 3))
		if (ft_ck_filetype(cubfile, clean_line, fd))
			cubfile->txpath[1] = ft_strdup(clean_line[1]);
	if (!ft_strncmp(clean_line[0], "WE", 3))
		if (ft_ck_filetype(cubfile, clean_line, fd))
			cubfile->txpath[2] = ft_strdup(clean_line[1]);
	if (!ft_strncmp(clean_line[0], "EA", 3))
		if (ft_ck_filetype(cubfile, clean_line, fd))
			cubfile->txpath[3] = ft_strdup(clean_line[1]);
	if (!ft_strncmp(clean_line[0], "S", 3))
		if (ft_ck_filetype(cubfile, clean_line, fd))
			cubfile->sppath[0] = ft_strdup(clean_line[1]);
	if (!ft_strncmp(clean_line[0], "F", 3))
		ft_ck_rgb(cubfile, clean_line, cubfile->rgbdw, fd);
	if (!ft_strncmp(clean_line[0], "C", 3))
		ft_ck_rgb(cubfile, clean_line, cubfile->rgbup, fd);
}

int		ft_id_n_load(t_file *cubfile, char *line, int fd)
{
	char	**clean_line;

	while (get_next_line(fd, &line) > 0 && cubfile->argcnt < 8)
	{
		clean_line = ft_split(line, ' ');
		if (clean_line[0] != NULL)
			ft_argtest(cubfile, clean_line, fd);
		free(line);
		if (clean_line != NULL)
			ft_free_c_line(clean_line);
	}
	free(line);
	if (cubfile->argcnt != 8)
	{
		printf("missing arguments in .cub file\n");
		ft_ex_wrongdata(cubfile, clean_line, fd);
	}
	return (TRUE);
}

int		ft_testmapchar(char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		while (ft_tstspc(line[i]))
			i++;
		if (line[i] == '1')
			return (TRUE);
		else
			return (FALSE);
	}
	return (FALSE);
}

void	ft_getmapdata(t_file *cubfile, char *line, int fd)
{
	int		linesize;

	while (get_next_line(fd, &line))
	{
		linesize = ft_strlen(line);
		if (linesize > cubfile->mapsize.w)
			cubfile->mapsize.w = linesize;
		if (linesize != 0)
			cubfile->mapsize.h++;
		free(line);
	}
	if (ft_testmapchar(line))
	{
		linesize = ft_strlen(line);
		if (linesize > cubfile->mapsize.w)
			cubfile->mapsize.w = linesize;
		if (linesize != 0)
			cubfile->mapsize.h++;
	}
	free(line);
}

void	ft_mapfill_1(t_file *cubfile, char *line, t_cnt *c)
{
	if (line[c->x] == ' ')
		cubfile->map[(cubfile->mapsize.w * c->y) + c->i] = 9;
}
