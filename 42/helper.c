/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarlos- <ocarlos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 09:29:52 by ocarlos-          #+#    #+#             */
/*   Updated: 2020/12/11 09:36:16 by ocarlos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// returns a color in hexadecimal format to use in minilibx
int		ft_crt_trgb(int t, int r, int g, int b)
{
	return(t << 24 | r << 16 | g << 8 | b);
}

// gets a color in minilibx format and returns its transparency
int		ft_get_t(int trgb)
{
	return (trgb & (0xFF << 24));
}

// gets a color in minilibx format and returns its red value
int		ft_get_r(int trgb)
{
	return (trgb & (0xFF << 16));
}

// gets a color in minilibx format and returns its green value
int		ft_get_g(int trgb)
{
	return (trgb & (0xFF << 8));
}

// gets a color in minilibx format and returns its blue value
int		ft_get_b(int trgb)
{
	return (trgb & 0xFF);
}

// get map stats (longest line, if is valid and map height)
int		ft_mapstats(int *map)
{
	//mapwidth
	//mapheight
	//isvalidmap
}

// reads map into an array
int		ft_maparray(int argc, char **argv)
{
	int		fd;
	char	*line;
	int		*map[SCREENW][SCREENH];

	if (argc > 2)
	{
		printf("Read a file or pipe a text");
		return (0);
	}
	else if (argc == 1)
		fd = 0;
	else if (argc == 2)
		fd = open(argv[1], O_RDONLY);
	else
		return (2);
	while (get_next_line(fd, &line))
	{
		printf("%lu - %s\n", ft_strlen(line), line);
		free(line);
	}
	printf("%lu - %s\n", ft_strlen(line), line);
	free(line);
	if (argc == 2)
		close(fd);
	return (TRUE);
}