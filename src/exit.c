/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarlos- <ocarlos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 16:09:30 by ocarlos-          #+#    #+#             */
/*   Updated: 2021/04/10 15:25:03 by ocarlos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
** void	ft_free_c_line(char **clean_line)
**      frees clean_line array of arrays
** void	ft_ex_wrongdata(t_file *file, int fd)
**      exits cleanly if error found in cub file
** void	ft_ex_wrongmap(t_file *file, int f)
**      exit function from map part of validation
** void	ft_error(void)
**      prints error message and finishes the program
** void	ft_finish(t_file *file, char *msg, int fd)
**		exits the programs and prints the error msg
*/

void	ft_free_c_line(char **clean_line)
{
	int	i;

	i = 0;
	if (clean_line != NULL)
		while (clean_line[i])
			if (clean_line[i] != NULL)
			{
				free(clean_line[i]);
				i++;
			}
	free(clean_line);
}

void	ft_ex_wrongdata(t_file *file, int fd)
{
	close(fd);
	if (file->txpath[0] != NULL)
		free(file->txpath[0]);
	if (file->txpath[1] != NULL)
		free(file->txpath[1]);
	if (file->txpath[2] != NULL)
		free(file->txpath[2]);
	if (file->txpath[3] != NULL)
		free(file->txpath[3]);
	if (file->sppath[0] != NULL)
		free(file->sppath[0]);
	exit(0);
}

void	ft_ex_wrongmap(t_file *file, int f)
{
	free(file->txpath[0]);
	free(file->txpath[1]);
	free(file->txpath[2]);
	free(file->txpath[3]);
	free(file->sppath[0]);
	if (f == 0)
		exit(0);
	free(file->map);
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

void	ft_finish(t_file *file, char *msg, int fd)
{
	printf("%s\n", msg);
	ft_ex_wrongdata(file, fd);
}