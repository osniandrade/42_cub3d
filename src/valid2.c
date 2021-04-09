/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarlos- <ocarlos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 16:09:30 by ocarlos-          #+#    #+#             */
/*   Updated: 2021/04/09 14:41:15 by ocarlos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
** int  ft_ck_mapdata(t_file *cubfile)
**		checks if map size ratio is valid
** int	ft_ck_validchar(int *map, t_cnt c, t_file *cubfile)
**		check characters around a zero
** int	ft_ck_sprite(t_file *cubfile, int *trgr)
**		checks if sprite has been located before
** void	ft_ck_validmap(t_file *cubfile)
**		tests for wall composing rules
** void	ft_rmblank(t_file *file)
**		removes blank spaces and identifier from argument line
*/

int		ft_ck_mapdata(t_file *cubfile)
{
	t_size	size;

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

int		ft_ck_validchar(int *map, t_cnt c, t_file *cubfile)
{
	if (map[ft_pos(c.j, c.x - 1, c.y - 1)] == 9 ||
		map[ft_pos(c.j, c.x - 1, c.y)] == 9 ||
		map[ft_pos(c.j, c.x - 1, c.y + 1)] == 9 ||
		map[ft_pos(c.j, c.x, c.y - 1)] == 9 ||
		map[ft_pos(c.j, c.x, c.y + 1)] == 9 ||
		map[ft_pos(c.j, c.x + 1, c.y - 1)] == 9 ||
		map[ft_pos(c.j, c.x + 1, c.y)] == 9 ||
		map[ft_pos(c.j, c.x + 1, c.y + 1)] == 9)
	{
		printf("map not enclosed\n");
		printf("wrong value at: x = %d, y = %d\n", c.x, c.y);
		ft_ex_wrongmap(cubfile, 1);
		return (FALSE);
	}
	else
		return (TRUE);
}

int		ft_ck_sprite(t_file *cubfile, int *trgr)
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
		return (FALSE);
	}
}

void	ft_ck_validmap(t_file *cubfile)
{
	t_cnt	c;
	int		*map;
	int		trgr;

	c = (t_cnt) {0};
	trgr = 0;
	c.i = cubfile->mapsize.h;
	c.j = cubfile->mapsize.w;
	map = cubfile->map;
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
	while (c.x < c.i * c.j)
		if (map[c.x++] == 9)
			map[c.x - 1] = 1;
}

void	ft_rmblank(t_file *file)
{
	int i;
	int j;
	int s;

	i = 0;
	s = ft_strlen(file->line);
	while (i < s)
	{
		if (ft_tstspc(file->line[i]) == 1 || file->line[i] == 'C' ||
			file->line[i] == 'F')
		{
			j = i;
			while (file->line[j])
			{
				file->line[j] = file->line[j + 1];
				j++;
			}
			s--;
		}
		i++;
	}
}
