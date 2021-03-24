/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadfile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarlos- <ocarlos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 08:46:18 by ocarlos-          #+#    #+#             */
/*   Updated: 2021/03/24 16:34:29 by ocarlos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*******************************************************************************
 * EXIT FUNCTIONS
 *******************************************************************************/

// exits cleanly if error found in cub file
void	ft_ex_wrongdata(t_filedata *cubfile, char **clean_line, int fd)
{
	close(fd);
	if (cubfile->tex_path[0] != NULL)
		free(cubfile->tex_path[0]);
	if (cubfile->tex_path[1] != NULL)
		free(cubfile->tex_path[1]);
	if (cubfile->tex_path[2] != NULL)
		free(cubfile->tex_path[2]);
	if (cubfile->tex_path[3] != NULL)
		free(cubfile->tex_path[3]);
	if (cubfile->spr_path[0] != NULL)
		free(cubfile->spr_path[0]);
	free(clean_line);
	exit(0);
}

// exit function from map part of validation
void	ft_ex_wrongmap(t_filedata *cubfile, int f)
{
	free(cubfile->tex_path[0]);
	free(cubfile->tex_path[1]);
	free(cubfile->tex_path[2]);
	free(cubfile->tex_path[3]);
	free(cubfile->spr_path[0]);
	if (f == 0)
		exit(0);
	free(cubfile->map);
	exit(0);
}

// prints error message and finishes the program
void	ft_error(void)
{
	int err;

	err = errno;
	if (err)
	{
		printf("%s\n", strerror(err));
		exit(0);
	}
}

/*******************************************************************************
 * DATA VALIDATION FUNCTIONS
 *******************************************************************************/

// checks if necessary files were loaded as args
void	ft_validargs(t_filedata *cubfile, int argc, char **argv)
{
	if (argc == 1)
	{
		printf("missing .cub file\n");
		exit(0);
	}
	if (argc >= 2)
		if (!ft_ck_fileext(argv[1], "cub"))
		{
			printf("wrong file extension\n");
			exit(0);
		}
	if (argc == 3)
	{
		if (ft_strncmp(argv[2], "--save", 6) != 0)
		{
			printf("invalid argument\n");
			exit(0);
		}
		cubfile->savebmp = 1;
	}
	if (argc > 3)
	{
		printf("too many arguments\n");
		exit(0);
	}
}

// checks if screen resolution is valid
t_sizedata ft_ck_scrsize(t_filedata *cubfile, char **clean_line, int fd)
{
	t_sizedata size;
	int	ratio;

	if (clean_line[1] == NULL || clean_line[2] == NULL)
	{
		printf("missing screen resolution data\n");
		ft_ex_wrongdata(cubfile, clean_line, fd);
	}
	size.w = ft_atoi(clean_line[1]);
	size.h = ft_atoi(clean_line[2]);
	ratio = size.w / 4;
	if (size.w % 4 != 0 || size.h % 4 != 0)
	{
		printf("invalid screen resolution\n");
		ft_ex_wrongdata(cubfile, clean_line, fd);
	}
	cubfile->argcount++;
	return (size);
}

// checks if file extension is equal to other parameter
int		ft_ck_fileext(char *line1, char *line2)
{
	int		ln;

	ln = ft_strlen(line1);
	if (ft_strncmp(&line1[ln - 3], line2, 3) == 0)
		return (TRUE);
	else
		return (FALSE);
}

// checks if informed file extension is .xpm
int		ft_ck_filetype(t_filedata *cubfile, char **clean_line, int fd)
{
	int	ln;

	ln = ft_strlen(clean_line[1]);
	if (ln == 0)
	{
		printf("missing file path\n");
		ft_ex_wrongdata(cubfile, clean_line, fd);
	}
	if (!ft_ck_fileext(clean_line[1], "xpm"))
	{
		printf("invalid file extension\n");
		ft_ex_wrongdata(cubfile, clean_line, fd);
	}
	if (access(clean_line[1], F_OK) != 0)
	{
		printf("file '%s' does not exist\n", clean_line[1]);
		ft_ex_wrongdata(cubfile, clean_line, fd);
	}
	cubfile->argcount++;
	return (TRUE);
}

// checks if rgb values are valid
void	ft_ck_rgbvalues(t_filedata *cubfile, char **clean_line, int *rgb, int fd)
{
	char **rgb_line;
	int j = 0;

	rgb_line = ft_split(clean_line[1], ',');
	if (rgb_line[0] == NULL || rgb_line[1] == NULL || rgb_line[2] == NULL)
	{
		printf("missing color value\n");
		free(rgb_line);
		ft_ex_wrongdata(cubfile, clean_line, fd);
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
			ft_ex_wrongdata(cubfile, clean_line, fd);
		}
		j++;
	}
	cubfile->argcount++;
}

// checks if map size ratio is valid
int		ft_ck_mapdata(t_filedata *cubfile)
{
	t_sizedata	size;
	int			ratio;

	size = cubfile->mapsize;
	if (size.h == 0 || size.w == 0)
	{
		printf("missing map size data\n");
		ft_ex_wrongmap(cubfile, 0);
	}
	if (size.h <= 3 || size.w <= 3)
	{
		printf("map is too small\n");
		ft_ex_wrongmap(cubfile, 0);
	}
	return (TRUE);
}

// check characters around a zero
int		ft_ck_validchar(int *map, t_count c, t_filedata *cubfile)
{
	if (map[ft_pos(c.j, c.x-1, c.y-1)] == 9 ||
		map[ft_pos(c.j, c.x-1, c.y)] == 9 ||
		map[ft_pos(c.j, c.x-1, c.y+1)] == 9 ||
		map[ft_pos(c.j, c.x, c.y-1)] == 9 ||
		map[ft_pos(c.j, c.x, c.y+1)] == 9 ||
		map[ft_pos(c.j, c.x+1, c.y-1)] == 9 ||
		map[ft_pos(c.j, c.x+1, c.y)] == 9 ||
		map[ft_pos(c.j, c.x+1, c.y+1)] == 9)
	{
		printf("map not enclosed\n");
		printf("wrong value at: x = %d, y = %d\n", c.x, c.y);
		ft_ex_wrongmap(cubfile, 1);
	}
	// if (map[ft_pos(c.j, c.x-1, c.y-1)] == 9)
	// 	if (map[ft_pos(c.j, c.x-1, c.y)] == 9)
	// 		if (map[ft_pos(c.j, c.x-1, c.y+1)] == 9)
	// 			if (map[ft_pos(c.j, c.x, c.y-1)] == 9)
	// 				if (map[ft_pos(c.j, c.x, c.y+1)] == 9)
	// 					if (map[ft_pos(c.j, c.x+1, c.y-1)] == 9)
	// 						if (map[ft_pos(c.j, c.x+1, c.y)] == 9)
	// 							if (map[ft_pos(c.j, c.x+1, c.y+1)] == 9)
	// 								{
	// 									printf("map not enclosed\n");
	// 									printf("wrong value at: x = %d, y = %d\n", c.x, c.y);
	// 									ft_ex_wrongmap(cubfile, 1);
	// 								}
	else
		return (TRUE);
}

// checks if sprite has been located before
int		ft_ck_sprite(t_filedata *cubfile, int *trgr)
{
	if (*trgr == 0)
	{
		*trgr = 1;
		return (TRUE);
	}
	else
	{
		printf("more than 1 sprite\n");
		ft_ex_wrongmap(cubfile, 1);
	}
}

// tests for wall composing rules
void	ft_ck_validmap(t_filedata *cubfile)
{
	t_count	c;
	int		*map;
	int		trgr;

	c = (t_count) {0};
	trgr = 0;
	c.i = cubfile->mapsize.h;
	c.j = cubfile->mapsize.w;
	map = cubfile->map;
	while (c.y < c.i)
	{
		while (c.x < c.j)
		{
			printf("%d ", cubfile->map[ft_pos(c.j, c.x, c.y)]);
			c.x++;
		}
		c.x = 0;
		c.y++;
		printf("\n");
	}
	c.x = 0;
	c.y = 0;
	while (c.y < c.i)
	{
		while (c.x < c.j)
		{
			if (map[ft_pos(c.j, c.x, c.y)] == 0)
				ft_ck_validchar(map, c, cubfile);
			if (map[ft_pos(c.j, c.x, c.y)] == 2)
				ft_ck_sprite(cubfile, &trgr);
			c.x++;
		}
		c.x = 0;
		c.y++;
	}
	c.x = 0;
	while (c.x < c.i * c.j)
		if (map[c.x++] == 9)
			map[c.x-1] = 1;
}

/*******************************************************************************
 * DATA LOADING FUNCTIONS
 *******************************************************************************/

// tests for every argument in the .cub file
void	ft_argtest(t_filedata *cubfile, char **clean_line, int fd)
{
	if (!ft_strncmp(clean_line[0], "R", 3))
		cubfile->scrsize = ft_ck_scrsize(cubfile, clean_line, fd);
	if (!ft_strncmp(clean_line[0], "NO", 3))
		if (ft_ck_filetype(cubfile, clean_line, fd))
			cubfile->tex_path[0] = ft_strdup(clean_line[1]);
	if (!ft_strncmp(clean_line[0], "SO", 3))
		if (ft_ck_filetype(cubfile, clean_line, fd))
			cubfile->tex_path[1] = ft_strdup(clean_line[1]);
	if (!ft_strncmp(clean_line[0], "WE", 3))
		if (ft_ck_filetype(cubfile, clean_line, fd))
			cubfile->tex_path[2] = ft_strdup(clean_line[1]);
	if (!ft_strncmp(clean_line[0], "EA", 3))
		if (ft_ck_filetype(cubfile, clean_line, fd))
			cubfile->tex_path[3] = ft_strdup(clean_line[1]);
	if (!ft_strncmp(clean_line[0], "S", 3))
		if (ft_ck_filetype(cubfile, clean_line, fd))
			cubfile->spr_path[0] = ft_strdup(clean_line[1]);
	if (!ft_strncmp(clean_line[0], "F", 3))
		ft_ck_rgbvalues(cubfile, clean_line, cubfile->rgbdw, fd);
	if (!ft_strncmp(clean_line[0], "C", 3))
		ft_ck_rgbvalues(cubfile, clean_line, cubfile->rgbup, fd);
}

// identifies the type of data and load into defined fields
int		ft_id_n_load(t_filedata *cubfile, char *line, int fd)
{
	char **clean_line;

	while (get_next_line(fd, &line) > 0 && cubfile->argcount < 8)
	{
		clean_line = ft_split(line, ' ');
		if (clean_line[0] != NULL)
			ft_argtest(cubfile, clean_line, fd);
	}
	if (cubfile->argcount != 8)
	{
		printf("missing arguments in .cub file\n");
		ft_ex_wrongdata(cubfile, clean_line, fd);
	}
	free(clean_line);
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
	if (ft_testmapchar(line))
	{
		linesize = ft_strlen(line);
		if (linesize > cubfile->mapsize.w)
			cubfile->mapsize.w = linesize;
		if (linesize != 0)
			cubfile->mapsize.h++;
	}
}

// checks map position for empty spaces (' ')
void	ft_mapfill_1(t_filedata *cubfile, char *line, t_count *c)
{
	if (line[c->x] == ' ')
		cubfile->map[(cubfile->mapsize.w * c->y) + c->i] = 9;
}

// checks map position for player start position
void	ft_mapfill_2(t_filedata *cubfile, char *line, t_count *c)
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
		cubfile->plrstart.x = c->x * TILE_SIZE;
		cubfile->plrstart.y = c->y * TILE_SIZE;
	}
}

// checks map position for wall, walk area or sprite positions
void	ft_mapfill_3(t_filedata *cubfile, char *line, t_count *c)
{
	if (line[c->x] == '0' || line[c->x] == '1' || line[c->x] == '2')
		cubfile->map[ft_pos(c->j, c->i, c->y)] = line[c->x] - 48;
}

// tests for the character and fills the struct array
void	ft_mapfill(t_filedata *cubfile, char *line, t_count *c)
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

// fills the map array with the .cub file info
void	ft_processmap(t_filedata *cubfile, char *line, int fd)
{
	t_count c;

	c = (t_count) {0};
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
	}
	if (ft_testmapchar(line))
		while (c.i < cubfile->mapsize.w)
			ft_mapfill(cubfile, line, &c);
}

// loads the .cub file into the struct
void	ft_load_cub_file(t_data *data, int argc, char **argv)
{
	t_filedata	cubfile;
	int			fd;
	char		*line;

	errno = 0;
	cubfile = (t_filedata) {0};
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
	data->cub = cubfile;
}