/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarlos- <ocarlos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 16:09:30 by ocarlos-          #+#    #+#             */
/*   Updated: 2021/03/31 09:58:43 by ocarlos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
** void	ft_free_c_line(char **clean_line)
**      frees clean_line array of arrays
** void	ft_ex_wrongdata(t_file *cubfile, char **clean_line, int fd)
**      exits cleanly if error found in cub file
** void	ft_ex_wrongmap(t_file *cubfile, int f)
**      exit function from map part of validation
** void	ft_error(void)
**      prints error message and finishes the program
*/

void	ft_free_c_line(char **clean_line)
{
	int	i;

	i = 0;
	while (clean_line[i])
		if (clean_line[i] != NULL)
			free(clean_line[i++]);
	free(clean_line);
}

void	ft_ex_wrongdata(t_file *cubfile, char **clean_line, int fd)
{
	close(fd);
	if (cubfile->txpath[0] != NULL)
		free(cubfile->txpath[0]);
	if (cubfile->txpath[1] != NULL)
		free(cubfile->txpath[1]);
	if (cubfile->txpath[2] != NULL)
		free(cubfile->txpath[2]);
	if (cubfile->txpath[3] != NULL)
		free(cubfile->txpath[3]);
	if (cubfile->sppath[0] != NULL)
		free(cubfile->sppath[0]);
	if (clean_line != NULL)
		ft_free_c_line(clean_line);
	exit(0);
}

void	ft_ex_wrongmap(t_file *cubfile, int f)
{
	free(cubfile->txpath[0]);
	free(cubfile->txpath[1]);
	free(cubfile->txpath[2]);
	free(cubfile->txpath[3]);
	free(cubfile->sppath[0]);
	if (f == 0)
		exit(0);
	free(cubfile->map);
	exit(0);
}

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
