/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarlos- <ocarlos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 16:09:30 by ocarlos-          #+#    #+#             */
/*   Updated: 2021/04/10 15:24:31 by ocarlos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
** void	ft_validargs(t_file *file, int argc, char **argv)
**      checks if necessary files were loaded as args
** t_size ft_ck_scrsize(t_file *file, char **clean_line, int fd)
**      checks if screen resolution is valid
** int	ft_ck_fileext(char *line1, char *line2)
**      checks if file extension is equal to other parameter
** int	ft_ck_filetype(t_file *file, char **clean_line, int fd)
**      checks if informed file extension is .xpm
** void	ft_ck_rgb(t_file *file, char **clean_line, int *rgb, int fd)
**      checks if rgb values are valid
*/

void	ft_validargs(t_file *file, int argc, char **argv)
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
		file->bmp = 1;
	}
	if (argc > 3)
	{
		printf("too many arguments\n");
		exit(0);
	}
}

t_size	ft_ck_scrsize(t_file *file, char **clean_line, int fd)
{
	t_size	size;

	if (clean_line[1] == NULL || clean_line[2] == NULL)
		ft_finish(file, "missing screen resolution data", fd);
	size.w = ft_atoi(clean_line[1]);
	size.h = ft_atoi(clean_line[2]);
	if (size.w % 4 != 0 || size.h % 4 != 0)
		ft_finish(file, "invalid screen resolution", fd);
	file->argcnt++;
	ft_loadedargs(file, 0, 0);
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

int		ft_ck_filetype(t_file *file, char **clean_line, int fd)
{
	int		ln;

	ln = ft_strlen(clean_line[1]);
	if (ln == 0)
		ft_finish(file, "missing file path", fd);
	if (clean_line[2] != NULL)
		ft_finish(file, "too many file paths", fd);
	if (!ft_ck_fileext(clean_line[1], "xpm"))
		ft_finish(file, "invalid file extension", fd);
	if (access(clean_line[1], F_OK) != 0)
		ft_finish(file, "one of the files informed does not exist", fd);
	ft_loadedargs(file, ft_argnumber(clean_line), 0);
	file->argcnt++;
	return (TRUE);
}

void	ft_ck_rgb(t_file *file, char **clean_line, int *rgb, int fd)
{
	char	**rgb_line;
	int		j;

	j = 0;
	ft_rmblank(file);
	rgb_line = ft_split(file->line, ',');
	if (rgb_line[0] == NULL || rgb_line[1] == NULL || rgb_line[2] == NULL)
	{
		if (rgb_line != NULL)
			ft_free_c_line(rgb_line);
		ft_finish(file, "missing color value", fd);
	}
	rgb[0] = ft_atoi(rgb_line[0]);
	rgb[1] = ft_atoi(rgb_line[1]);
	rgb[2] = ft_atoi(rgb_line[2]);
	if (rgb_line != NULL)
		ft_free_c_line(rgb_line);
	while (j < 3)
		if (rgb[j] < 0 || rgb[j++] > 255)
			ft_finish(file, "invalid color values", fd);
	ft_loadedargs(file, ft_argnumber(clean_line), 0);
	file->argcnt++;
}
