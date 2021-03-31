/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarlos- <ocarlos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 16:09:30 by ocarlos-          #+#    #+#             */
/*   Updated: 2021/03/31 10:30:57 by ocarlos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
** void	ft_validargs(t_file *cubfile, int argc, char **argv)
**      checks if necessary files were loaded as args
** t_size ft_ck_scrsize(t_file *cubfile, char **clean_line, int fd)
**      checks if screen resolution is valid
** int	ft_ck_fileext(char *line1, char *line2)
**      checks if file extension is equal to other parameter
** int	ft_ck_filetype(t_file *cubfile, char **clean_line, int fd)
**      checks if informed file extension is .xpm
** void	ft_ck_rgbvalues(t_file *cubfile, char **clean_line, int *rgb, int fd)
**      checks if rgb values are valid
*/

void	ft_validargs(t_file *cubfile, int argc, char **argv)
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
		cubfile->bmp = 1;
	}
	if (argc > 3)
	{
		printf("too many arguments\n");
		exit(0);
	}
}

t_size ft_ck_scrsize(t_file *cubfile, char **clean_line, int fd)
{
	t_size	size;

	if (clean_line[1] == NULL || clean_line[2] == NULL)
	{
		printf("missing screen resolution data\n");
		ft_ex_wrongdata(cubfile, clean_line, fd);
	}
	size.w = ft_atoi(clean_line[1]);
	size.h = ft_atoi(clean_line[2]);
	if (size.w % 4 != 0 || size.h % 4 != 0)
	{
		printf("invalid screen resolution\n");
		ft_ex_wrongdata(cubfile, clean_line, fd);
	}
	cubfile->argcnt++;
	return (size);
}

int		ft_ck_fileext(char *line1, char *line2)
{
	int		ln;

	ln = ft_strlen(line1);
	if (ft_strncmp(&line1[ln - 3], line2, 3) == 0)
		return (TRUE);
	else
		return (FALSE);
}

int		ft_ck_filetype(t_file *cubfile, char **clean_line, int fd)
{
	int		ln;

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
	cubfile->argcnt++;
	return (TRUE);
}

void	ft_ck_rgbvalues(t_file *cubfile, char **clean_line, int *rgb, int fd)
{
	char	**rgb_line;
	int		j;

	j = 0;
	rgb_line = ft_split(clean_line[1], ',');
	if (rgb_line[0] == NULL || rgb_line[1] == NULL || rgb_line[2] == NULL)
	{
		printf("missing color value\n");
		if (rgb_line != NULL)
			ft_free_c_line(rgb_line);
		ft_ex_wrongdata(cubfile, clean_line, fd);
	}
	rgb[0] = ft_atoi(rgb_line[0]);
	rgb[1] = ft_atoi(rgb_line[1]);
	rgb[2] = ft_atoi(rgb_line[2]);
	if (rgb_line != NULL)
		ft_free_c_line(rgb_line);
	while (j < 3)
	{
		if (rgb[j] < 0 || rgb[j] > 255)
		{
			printf("invalid color values\n");
			ft_ex_wrongdata(cubfile, clean_line, fd);
		}
		j++;
	}
	cubfile->argcnt++;
}
