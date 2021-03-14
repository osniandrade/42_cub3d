/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadfile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarlos- <ocarlos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 08:46:18 by ocarlos-          #+#    #+#             */
/*   Updated: 2021/03/14 12:36:42 by ocarlos-         ###   ########.fr       */
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

int		ft_identify(t_filedata *cubfile, char *line)
{
	char **clean_line;
	int i = 0;
	int linesize;

	clean_line = ft_split(line, ' ');
	while (clean_line[i] != NULL)
	{
		if (!ft_strncmp(clean_line[i], "R", 3))
		{
			cubfile->scrsize.w = ft_atoi(clean_line[++i]);
			cubfile->scrsize.h = ft_atoi(clean_line[++i]);
			printf("loaded screen resolution\n");
		}
		if (!ft_strncmp(clean_line[i], "NO", 3))
		{
			linesize = ft_strlen(clean_line[++i]);
			ft_memcpy(&cubfile->tex_path[0], &clean_line[i], linesize);
			printf("loaded north texture\n");
		}
		if (!ft_strncmp(clean_line[i], "SO", 3))
		{
			linesize = ft_strlen(clean_line[++i]);
			ft_memcpy(&cubfile->tex_path[1], &clean_line[i], linesize);
			printf("loaded south texture\n");
		}
		if (!ft_strncmp(clean_line[i], "WE", 3))
		{
			linesize = ft_strlen(clean_line[++i]);
			ft_memcpy(&cubfile->tex_path[2], &clean_line[i], linesize);
			printf("loaded east texture\n");
		}
		if (!ft_strncmp(clean_line[i], "EA", 3))
		{
			linesize = ft_strlen(clean_line[++i]);
			ft_memcpy(&cubfile->tex_path[3], &clean_line[i], linesize);
			printf("loaded west texture\n");
		}
		if (!ft_strncmp(clean_line[i], "S", 3))
		{
			linesize = ft_strlen(clean_line[++i]);
			ft_memcpy(&cubfile->spr_path[0], &clean_line[i], linesize);
			printf("loaded sprite texture\n");
		}
		else
		{
			i++;
		}
	}
}

void	ft_load_cub_file(t_data *data, int argc, char **argv)
{
	t_filedata	cubfile;
	int			fd;
	char		*line;

	//printf("%s\n", argv[1]);
	fd = open(argv[1], O_RDONLY);
	line = NULL;

	while (get_next_line(fd, &line) > 0)
	{
		ft_identify(&cubfile, line);
	}
	// get_next_line(fd, &line);
	// ft_identify(data, line);

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