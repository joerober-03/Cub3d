/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dferreir <dferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 11:36:58 by dferreir          #+#    #+#             */
/*   Updated: 2023/08/23 10:23:18 by dferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_square(t_var *v, double step_x, double step_y)
{
	double	x;
	double	y;
	double	new_step_x;
	double	new_step_y;

	new_step_x = step_x * v->map.index_x + 2;
	new_step_y = step_y * v->map.index_y + 1;
	y = new_step_y - 1;
	while (++y <= new_step_y + step_y - 2)
	{
		x = new_step_x - 1;
		while (++x <= new_step_x + step_x - 2)
			my_mlx_pixel_put(v, x, y, 0x00FF00);
	}
}

void	mini_player(t_var *v)
{
	v->map.initial_y = (int)(v->map.total_y * v->pos.pos_y / v->map.map_height);
	v->map.initial_x = (int)(v->map.total_x * v->pos.pos_x / v->map.map_width);
	my_mlx_pixel_put(v, v->map.initial_y, v->map.initial_x + 1, 0xFF0000);
	my_mlx_pixel_put(v, v->map.initial_y, v->map.initial_x - 1, 0xFF0000);
	my_mlx_pixel_put(v, v->map.initial_y + 1, v->map.initial_x, 0xFF0000);
	my_mlx_pixel_put(v, v->map.initial_y - 1, v->map.initial_x, 0xFF0000);
	my_mlx_pixel_put(v, v->map.initial_y + 1, v->map.initial_x + 1, 0xFF0000);
	my_mlx_pixel_put(v, v->map.initial_y + 1, v->map.initial_x - 1, 0xFF0000);
	my_mlx_pixel_put(v, v->map.initial_y - 1, v->map.initial_x + 1, 0xFF0000);
	my_mlx_pixel_put(v, v->map.initial_y - 1, v->map.initial_x - 1, 0xFF0000);
	my_mlx_pixel_put(v, v->map.initial_y, v->map.initial_x + 2, 0xFF0000);
	my_mlx_pixel_put(v, v->map.initial_y, v->map.initial_x - 2, 0xFF0000);
	my_mlx_pixel_put(v, v->map.initial_y + 2, v->map.initial_x, 0xFF0000);
	my_mlx_pixel_put(v, v->map.initial_y - 2, v->map.initial_x, 0xFF0000);
	my_mlx_pixel_put(v, v->map.initial_y + (double)(v->pos.dir_y * 2),
		v->map.initial_x + (double)(v->pos.dir_x * 2), 0xFF0000);
	my_mlx_pixel_put(v, v->map.initial_y + (double)(v->pos.dir_y * 3),
		v->map.initial_x + (double)(v->pos.dir_x * 3), 0xFF0000);
	my_mlx_pixel_put(v, v->map.initial_y + (double)(v->pos.dir_y * 4),
		v->map.initial_x + (double)(v->pos.dir_x * 4), 0xFF0000);
	my_mlx_pixel_put(v, v->map.initial_y + (double)(v->pos.dir_y * 5),
		v->map.initial_x + (double)(v->pos.dir_x * 5), 0xFF0000);
}

void	mini_map_walls(t_var *v)
{
	double	step_x;
	double	step_y;

	step_x = (int)((double)v->map.total_x / (double)v->map.map_width);
	step_y = (int)((double)v->map.total_y / (double)v->map.map_height);
	v->map.index_y = -1;
	while (++v->map.index_y < v->map.map_height)
	{
		v->map.index_x = -1;
		while (++v->map.index_x < v->map.map_width)
			if (v->map.map[v->map.index_y][v->map.index_x] == 1)
				print_square(v, step_x, step_y);
	}
}

void	mini_map_base(t_var *v)
{
	int		x;
	int		y;

	if (v->map.map_width >= v->map.map_height)
	{
		v->map.total_x = 300;
		v->map.total_y = v->map.map_height * 300 / v->map.map_width;
	}
	else
	{
		v->map.total_y = 300;
		v->map.total_x = v->map.map_width * 300 / v->map.map_height;
	}
	y = -1;
	while (++y < v->map.total_y)
	{
		x = -1;
		while (++x < v->map.total_x)
			my_mlx_pixel_put(v, x, y, 0x000000);
	}
	mini_map_walls(v);
	mini_player(v);
}
