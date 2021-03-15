/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadfile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarlos- <ocarlos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 08:46:18 by ocarlos-          #+#    #+#             */
/*   Updated: 2021/03/15 19:46:10 by ocarlos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*******************************************************************************
 * TEMPORARY
 *******************************************************************************/

// map matrix (TEMPORARY)
int map[MAP_ROWS * MAP_COLS] = {
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1,
	1, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1,
	1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1,
	1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

// textures paths (TEMPORARY)
static char *texpath[TEXTURE_COUNT] = {
	"./img/stonewall.xpm",
	"./img/moldystonewall.xpm",
	"./img/labwall.xpm",
	"./img/bunkerwall.xpm"};

// sprites paths (TEMPORARY)
static char *sprpath[SPRITE_COUNT] = {
	"./img/armor.xpm"};

/*******************************************************************************
 * FILE DATA FUNCTIONS
 *******************************************************************************/

int		ft_id_n_load(t_filedata *cubfile, char *line)
{
	char **clean_line;
	char **rgb_line;
	int i = 0;

	clean_line = ft_split(line, ' ');
	while (clean_line[i] != NULL)
	{
		if (!ft_strncmp(clean_line[i], "R", 3))
		{
			cubfile->scrsize.w = ft_atoi(clean_line[++i]);
			cubfile->scrsize.h = ft_atoi(clean_line[++i]);
			printf("loaded screen resolution\n");
			cubfile->argcount++;
			return (TRUE);
		}
		if (!ft_strncmp(clean_line[i], "NO", 3))
		{
			cubfile->tex_path[0] = ft_strdup(clean_line[++i]);
			printf("loaded north texture\n");
			cubfile->argcount++;
			return (TRUE);
		}
		if (!ft_strncmp(clean_line[i], "SO", 3))
		{
			cubfile->tex_path[1] = ft_strdup(clean_line[++i]);
			printf("loaded south texture\n");
			cubfile->argcount++;
			return (TRUE);
		}
		if (!ft_strncmp(clean_line[i], "WE", 3))
		{
			cubfile->tex_path[2] = ft_strdup(clean_line[++i]);
			printf("loaded east texture\n");
			cubfile->argcount++;
			return (TRUE);
		}
		if (!ft_strncmp(clean_line[i], "EA", 3))
		{
			cubfile->tex_path[3] = ft_strdup(clean_line[++i]);
			printf("loaded west texture\n");
			cubfile->argcount++;
			return (TRUE);
		}
		if (!ft_strncmp(clean_line[i], "S", 3))
		{
			cubfile->spr_path[0] = ft_strdup(clean_line[++i]);
			printf("loaded sprite texture\n");
			cubfile->argcount++;
			return (TRUE);
		}
		if (!ft_strncmp(clean_line[i], "F", 3))
		{
			rgb_line = ft_split(clean_line[1], ',');
			cubfile->rgbdw[0] = ft_atoi(rgb_line[0]);
			cubfile->rgbdw[1] = ft_atoi(rgb_line[1]);
			cubfile->rgbdw[2] = ft_atoi(rgb_line[2]);
			printf("loaded floor colors\n");
			cubfile->argcount++;
			return (TRUE);
		}
		if (!ft_strncmp(clean_line[i], "C", 3))
		{
			rgb_line = ft_split(clean_line[1], ',');
			cubfile->rgbup[0] = ft_atoi(rgb_line[0]);
			cubfile->rgbup[1] = ft_atoi(rgb_line[1]);
			cubfile->rgbup[2] = ft_atoi(rgb_line[2]);
			printf("loaded ceiling colors\n");
			cubfile->argcount++;
			return (TRUE);
		}
		else
		{
			i++;
		}
	}
}

int		ft_processmap(t_filedata *cubfile, char *line, int fd)
{
	int		linesize;
	//int		previous;

	//previous = line;
	//printf("previous - %d\n", previous);
	while (get_next_line(fd, &line))
	{
		printf("%s\n", line);
		if (ft_strchr(line, '1') || ft_strchr(line, '0'))
		{
			linesize = ft_strlen(line);
			if (linesize > cubfile->mapsize.w)
				cubfile->mapsize.w = linesize;
			cubfile->mapsize.h++;
		}
		// WHAT SHOULD I DO FOR FUCKS SAKE
	}
	
}

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

	while (get_next_line(fd, &line) > 0 && cubfile.argcount < 8)
	{
		ft_id_n_load(&cubfile, line);
	}

	ft_processmap(&cubfile, line, fd);


	// get_next_line(fd, &line);
	// ft_id_n_load(data, line);

	// cubfile.tex_path[0] = "./img/stonewall.xpm";
	// cubfile.tex_path[1] = "./img/moldystonewall.xpm";
	// cubfile.tex_path[2] = "./img/labwall.xpm";
	// cubfile.tex_path[3] = "./img/bunkerwall.xpm";
	// cubfile.spr_path[0] = "./img/armor.xpm";
	//cubfile.scrsize.w = 1280;
	//cubfile.scrsize.h = 960;
	cubfile.mapsize.w = 20;
	cubfile.mapsize.h = 13;
	cubfile.map = map;
	data->cub = cubfile;
}