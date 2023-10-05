/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joerober <joerober@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 10:52:17 by joerober          #+#    #+#             */
/*   Updated: 2023/08/14 10:54:26 by joerober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

void	initiate_tex(t_var *v, char *path, int i)
{
	int	w;
	int	h;

	h = 64;
	w = 64;
	v->tex[i].ptr = mlx_xpm_file_to_image(v->mlx, path, &w, &h);
	if (v->tex[i].ptr == NULL)
		ft_error(v, "invalid texture path\n");
	v->tex[i].addr = mlx_get_data_addr(v->tex[i].ptr, &v->tex[i].bpp,
			&v->tex[i].size_line, &v->tex[i].endian);
	v->tex[i].is_init++;
	if (v->tex[i].is_init > 1)
		ft_error(v, "duplicate texture information\n");
}

void	change_dir(t_var *v, double multiplier)
{
	double	olddir_x;
	double	oldplane_x;

	olddir_x = v->pos.dir_x;
	oldplane_x = v->pos.plane_x;
	v->pos.dir_x = v->pos.dir_x * cos(multiplier)
		- v->pos.dir_y * sin(multiplier);
	v->pos.dir_y = olddir_x * sin(multiplier) + v->pos.dir_y * cos(multiplier);
	v->pos.plane_x = v->pos.plane_x * cos(multiplier)
		- v->pos.plane_y * sin(multiplier);
	v->pos.plane_y = oldplane_x * sin(multiplier)
		+ v->pos.plane_y * cos(multiplier);
}

void	ft_error(t_var *v, char *error)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(error, 2);
	(void) v;
	exit(1);
}

char	**mfree(char **tab)
{
	int		a;

	a = 0;
	while (tab[a])
	{
		free(tab[a]);
		a++;
	}
	free(tab);
	return (0);
}

int	close_hook(int button, t_var *v)
{
	(void)button;
	(void)v;
	exit(0);
	return (0);
}
