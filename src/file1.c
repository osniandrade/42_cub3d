/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarlos- <ocarlos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 16:09:30 by ocarlos-          #+#    #+#             */
/*   Updated: 2021/04/01 17:02:39 by ocarlos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
** void	ft_argtest(t_file *file, char **clean_line, int fd)
**		tests for every argument in the .cub file
** int	ft_id_n_load(t_file *file, char *line, int fd)
**		identifies the type of data and load into defined fields
** int	ft_testmapchar(char *line)
**		tests if the first valid char of a line is '1'
** void	ft_getmapdata(t_file *file, char *line, int fd)
**		loads the size of the map
** void	ft_mapfill_1(t_file *file, char *line, t_cnt *c)
**		checks map position for empty spaces (' ')
*/

void	ft_argtest(t_file *file, char **clean_line, int fd)
{
	if (!ft_strncmp(clean_line[0], "R", 3))
		file->scrsize = ft_ck_scrsize(file, clean_line, fd);
	if (!ft_strncmp(clean_line[0], "NO", 3))
		if (ft_ck_filetype(file, clean_line, fd))
			file->txpath[0] = ft_strdup(clean_line[1]);
	if (!ft_strncmp(clean_line[0], "SO", 3))
		if (ft_ck_filetype(file, clean_line, fd))
			file->txpath[1] = ft_strdup(clean_line[1]);
	if (!ft_strncmp(clean_line[0], "WE", 3))
		if (ft_ck_filetype(file, clean_line, fd))
			file->txpath[2] = ft_strdup(clean_line[1]);
	if (!ft_strncmp(clean_line[0], "EA", 3))
		if (ft_ck_filetype(file, clean_line, fd))
			file->txpath[3] = ft_strdup(clean_line[1]);
	if (!ft_strncmp(clean_line[0], "S", 3))
		if (ft_ck_filetype(file, clean_line, fd))
			file->sppath[0] = ft_strdup(clean_line[1]);
	if (!ft_strncmp(clean_line[0], "F", 3))
		ft_ck_rgb(file, clean_line, file->rgbdw, fd);
	if (!ft_strncmp(clean_line[0], "C", 3))
		ft_ck_rgb(file, clean_line, file->rgbup, fd);
}

int		ft_id_n_load(t_file *file, char *line, int fd)
{
	char	**clean_line;

	while (get_next_line(fd, &line) > 0 && file->argcnt < 8)
	{
		clean_line = ft_split(line, ' ');
		if (clean_line[0] != NULL)
			ft_argtest(file, clean_line, fd);
		free(line);
		if (clean_line != NULL)
			ft_free_c_line(clean_line);
	}
	free(line);
	if (file->argcnt != 8)
	{
		printf("missing arguments in .cub file\n");
		ft_ex_wrongdata(file, clean_line, fd);
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

void	ft_getmapdata(t_file *file, char *line, int fd)
{
	int		linesize;

	while (get_next_line(fd, &line))
	{
		linesize = ft_strlen(line);
		if (linesize > file->mapsize.w)
			file->mapsize.w = linesize;
		if (linesize != 0)
			file->mapsize.h++;
		free(line);
	}
	if (ft_testmapchar(line))
	{
		linesize = ft_strlen(line);
		if (linesize > file->mapsize.w)
			file->mapsize.w = linesize;
		if (linesize != 0)
			file->mapsize.h++;
	}
	free(line);
}

void	ft_mapfill_1(t_file *file, char *line, t_cnt *c)
{
	if (line[c->x] == ' ')
		file->map[(file->mapsize.w * c->y) + c->i] = 9;
}
