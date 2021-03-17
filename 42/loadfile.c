/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadfile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarlos- <ocarlos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 08:46:18 by ocarlos-          #+#    #+#             */
/*   Updated: 2021/03/17 16:56:58 by ocarlos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*******************************************************************************
 * EXIT FUNCTIONS
 *******************************************************************************/

// exits cleanly if error found in cub file
int	ft_exit(t_filedata *cubfile, char **clean_line, int i)
{
	free(clean_line);
	if (i == 0)
		exit(0);
	free(cubfile->tex_path[0]);
	if (i == 1)
		exit(0);
	free(cubfile->tex_path[1]);
	if (i == 2)
		exit(0);
	free(cubfile->tex_path[2]);
	if (i == 3)
		exit(0);
	free(cubfile->tex_path[3]);
	if (i == 4)
		exit(0);
	free(cubfile->spr_path[0]);
	if (i == 5)
		exit(0);
	exit(0);
}

/*******************************************************************************
 * DATA VALIDATION FUNCTIONS
 *******************************************************************************/

// checks if screen resolution is valid
t_sizedata ft_ck_scrsize(t_filedata *cubfile, char **clean_line)
{
	t_sizedata size;
	int	ratio;

	if (clean_line[1] == NULL || clean_line[2] == NULL)
	{
		printf("missing screen resolution data\n");
		ft_exit(cubfile, clean_line, 0);
	}
	size.w = ft_atoi(clean_line[1]);
	size.h = ft_atoi(clean_line[2]);
	ratio = size.w / 4;
	if (size.w % 4 != 0 || size.h % 4 != 0)
	{
		printf("invalid screen resolution\n");
		ft_exit(cubfile, clean_line, 0);
	}
	if (size.w != ratio * 4 || size.h != ratio * 3)
	{
		printf("invalid screen ratio\n");
		ft_exit(cubfile, clean_line, 0);
	}
	cubfile->argcount++;
	return (size);
}

// checks if informed file extension is .xpm
int		ft_ck_filetype(t_filedata *cubfile, char **clean_line, int i)
{
	int	ln;

	ln = ft_strlen(clean_line[1]);
	if (ln == 0)
	{
		printf("missing file path\n");
		ft_exit(cubfile, clean_line, 0);
	}
	if (clean_line[1][ln - 3] != 'x' ||
		clean_line[1][ln - 2] != 'p' ||
		clean_line[1][ln - 1] != 'm')
	{
		printf("invalid file extension\n");
		ft_exit(cubfile, clean_line, i);
	}
	cubfile->argcount++;
	return (TRUE);
}

// checks if rgb values are valid
void	ft_ck_rgbvalues(t_filedata *cubfile, char **clean_line, int *rgb, int i)
{
	char **rgb_line;
	int j = 0;

	rgb_line = ft_split(clean_line[1], ',');
	if (rgb_line[0] == NULL || rgb_line[1] == NULL || rgb_line[2] == NULL)
	{
		printf("missing color value\n");
		free(rgb_line);
		ft_exit(cubfile, clean_line, i);
	}
	rgb[0] = ft_atoi(rgb_line[0]);
	rgb[1] = ft_atoi(rgb_line[1]);
	rgb[2] = ft_atoi(rgb_line[2]);
	free(rgb_line);
	while (j < 3)
	{
		if (rgb[j] < 0 || rgb[j] > 255)
		{
			printf("invalid color values\n");
			ft_exit(cubfile, clean_line, i);
		}
		j++;
	}
	cubfile->argcount++;
}

/*******************************************************************************
 * DATA LOADING FUNCTIONS
 *******************************************************************************/

// identifies the type of data and load into defined fields
int		ft_id_n_load(t_filedata *cubfile, char *line, int fd)
{
	char **clean_line;
	char **rgb_line;

	while (get_next_line(fd, &line) > 0 && cubfile->argcount < 8)
	{
		clean_line = ft_split(line, ' ');
		if (clean_line[0] != NULL)
		{
			if (!ft_strncmp(clean_line[0], "R", 3))
				cubfile->scrsize = ft_ck_scrsize(cubfile, clean_line);
			if (!ft_strncmp(clean_line[0], "NO", 3))
				if (ft_ck_filetype(cubfile, clean_line, 0))
					cubfile->tex_path[0] = ft_strdup(clean_line[1]);
			if (!ft_strncmp(clean_line[0], "SO", 3))
				if (ft_ck_filetype(cubfile, clean_line, 1))
					cubfile->tex_path[1] = ft_strdup(clean_line[1]);
			if (!ft_strncmp(clean_line[0], "WE", 3))
				if (ft_ck_filetype(cubfile, clean_line, 2))
					cubfile->tex_path[2] = ft_strdup(clean_line[1]);
			if (!ft_strncmp(clean_line[0], "EA", 3))
				if (ft_ck_filetype(cubfile, clean_line, 3))
					cubfile->tex_path[3] = ft_strdup(clean_line[1]);
			if (!ft_strncmp(clean_line[0], "S", 3))
				if (ft_ck_filetype(cubfile, clean_line, 4))
					cubfile->spr_path[0] = ft_strdup(clean_line[1]);
			if (!ft_strncmp(clean_line[0], "F", 3))
				ft_ck_rgbvalues(cubfile, clean_line, cubfile->rgbdw, 5);
			if (!ft_strncmp(clean_line[0], "C", 3))
				ft_ck_rgbvalues(cubfile, clean_line, cubfile->rgbup, 5);
		}
	}
}

// tests if the first valid char of a line is '1'
int		ft_testmapchar(char *line)
{
	int i = 0;

	while (line[i])
	{
		while (ft_tstspc(line[i]))
			i++;
		if (line[i] == '1')
			return (TRUE);
		else
			return (FALSE);
	}
}

// loads the size of the map
void	ft_getmapdata(t_filedata *cubfile, char *line, int fd)
{
	int		linesize;

	while (get_next_line(fd, &line))
	{
		linesize = ft_strlen(line);
		if (linesize > cubfile->mapsize.w)
			cubfile->mapsize.w = linesize;
		if (linesize != 0)
			cubfile->mapsize.h++;
	}
}

// tests for the character and fills the struct array
void	ft_mapfill(t_filedata *cubfile, char *line, t_count *c)
{
	char temp;
	
	if (line[c->x])
	{
		if (line[c->x] == ' ')
			cubfile->map[(cubfile->mapsize.w * c->y) + c->i] = 1;
		if (line[c->x] == 'N' || line[c->x] == 'S' || line[c->x] == 'W' || line[c->x] == 'E')
		{
			cubfile->map[(cubfile->mapsize.w * c->y) + c->i] = 0;
			cubfile->plrdir = line[c->x];
		}
		if (line[c->x] == '0' || line[c->x] == '1' || line[c->x] == '2')
		{
			temp = line[c->x];
			cubfile->map[ft_pos(c->j, c->i, c->y)] = ft_atoi(&temp);
		}
		c->x++;
	}
	else
		cubfile->map[ft_pos(c->j, c->i, c->y)] = 1;
	c->i++;
}

// fills the map array with the .cub file info
void	ft_processmap(t_filedata *cubfile, char *line, int fd)
{
	t_count c;

	c = (t_count) {0};
	c.j = cubfile->mapsize.w;
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
	}
}

// loads the .cub file into the struct
void	ft_load_cub_file(t_data *data, int argc, char **argv)
{
	t_filedata	cubfile;
	int			fd;
	char		*line;

	fd = open(argv[1], O_RDONLY);
	line = NULL;
	cubfile.argcount = 0;
	cubfile.mapsize.h = 0;
	cubfile.mapsize.w = 0;
	ft_id_n_load(&cubfile, line, fd);
	ft_getmapdata(&cubfile, line, fd);
	close(fd);
	fd = open(argv[1], O_RDONLY);
	line = NULL;
	ft_processmap(&cubfile, line, fd);
	data->cub = cubfile;
	close(fd);
}