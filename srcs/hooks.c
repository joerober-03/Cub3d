/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dferreir <dferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 15:28:09 by dferreir          #+#    #+#             */
/*   Updated: 2023/08/22 14:12:30 by dferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

int	move1(t_var *v, int keycode)
{
	if (keycode == 13)
	{
		v->pos.pos_x += v->pos.dir_x * 0.2;
		v->pos.pos_y += v->pos.dir_y * 0.2;
		return (1);
	}
	else if (keycode == 0)
	{
		v->pos.pos_x -= v->pos.dir_y * 0.1;
		v->pos.pos_y += v->pos.dir_x * 0.1;
		return (1);
	}
	return (0);
}

int	move2(t_var *v, int keycode)
{
	if (keycode == 1)
	{
		v->pos.pos_x -= v->pos.dir_x * 0.1;
		v->pos.pos_y -= v->pos.dir_y * 0.1;
		return (1);
	}
	else if (keycode == 2)
	{
		v->pos.pos_x += v->pos.dir_y * 0.1;
		v->pos.pos_y -= v->pos.dir_x * 0.1;
		return (1);
	}
	return (0);
}

int	move3(t_var *v, int keycode)
{
	double	olddir_x;
	double	oldplane_x;

	olddir_x = v->pos.dir_x;
	oldplane_x = v->pos.plane_x;
	if (keycode == 123)
	{
		v->pos.dir_x = v->pos.dir_x * cos(0.06) - v->pos.dir_y * sin(0.06);
		v->pos.dir_y = olddir_x * sin(0.06) + v->pos.dir_y * cos(0.06);
		v->pos.plane_x = v->pos.plane_x * cos(0.06)
			- v->pos.plane_y * sin(0.06);
		v->pos.plane_y = oldplane_x * sin(0.06) + v->pos.plane_y * cos(0.06);
		return (1);
	}
	else if (keycode == 124)
	{
		v->pos.dir_x = v->pos.dir_x * cos(-0.06) - v->pos.dir_y * sin(-0.06);
		v->pos.dir_y = olddir_x * sin(-0.06) + v->pos.dir_y * cos(-0.06);
		v->pos.plane_x = v->pos.plane_x * cos(-0.06)
			- v->pos.plane_y * sin(-0.06);
		v->pos.plane_y = oldplane_x * sin(-0.06) + v->pos.plane_y * cos(-0.06);
		return (1);
	}
	return (0);
}

int	keyhook(int keycode, t_var *v)
{
	int		r;

	r = 0;
	if (keycode == 53 && ++r)
		exit(0);
	r += move1(v, keycode);
	r += move2(v, keycode);
	r += move3(v, keycode);
	if (keycode == 46 && ++r)
		v->map.show_map += 1;
	else if (keycode == 8 && ++r)
		v->map.show_crosshair += 1;
	if (r != 0)
	{
		mlx_destroy_image(v->mlx, v->image.img);
		mlx_clear_window(v->mlx, v->mlx_win);
		display(v);
	}
	return (0);
}

int	mouse_move(int x, int y, t_var *v)
{
	double	olddir_x;
	double	oldplane_x;
	double	z;

	(void)x;
	(void)y;
	z = (double)(v->pos.mouse_x - x) / 450;
	olddir_x = v->pos.dir_x;
	oldplane_x = v->pos.plane_x;
	v->pos.dir_x = v->pos.dir_x * cos(z) - v->pos.dir_y * sin(z);
	v->pos.dir_y = olddir_x * sin(z) + v->pos.dir_y * cos(z);
	v->pos.plane_x = v->pos.plane_x * cos(z) - v->pos.plane_y * sin(z);
	v->pos.plane_y = oldplane_x * sin(z) + v->pos.plane_y * cos(z);
	v->pos.mouse_x = x;
	mlx_destroy_image(v->mlx, v->image.img);
	mlx_clear_window(v->mlx, v->mlx_win);
	display(v);
	return (0);
}
