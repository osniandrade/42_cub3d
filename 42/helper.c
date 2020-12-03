/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarlos- <ocarlos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 09:29:52 by ocarlos-          #+#    #+#             */
/*   Updated: 2020/12/03 17:02:39 by ocarlos-         ###   ########.fr       */
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

// gets line size
int		ft_getlinesize(char *line)
{
	int size = 0;
	while (line[size] == '1' || line[size] == '0')
		size++;
	return (size);
}

// reads map into an array
int		ft_maparray(int argc, char **argv)
{
	int		fd;
	char	*line;
	int		*map[][];

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
		printf("%d - %s\n", ft_getlinesize(line), line);
		free(line);
	}
	printf("%d - %s\n", ft_getlinesize(line), line);
	free(line);
	if (argc == 2)
		close(fd);
	return (TRUE);
}