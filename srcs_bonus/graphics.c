/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joerober <joerober@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 09:56:07 by joerober          #+#    #+#             */
/*   Updated: 2023/08/14 10:26:02 by joerober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

void	my_mlx_pixel_put(t_var *v, int x, int y, int color)
{
	char	*dst;

	if (x <= SCREENW && x >= 0 && y <= SCREENH && y >= 0)
	{
		dst = v->image.addr + (y * v->image.line_length
				+ x * (v->image.bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

void	background_display(t_var *v)
{
	int	i;
	int	j;
	int	color;

	i = -1;
	j = -1;
	color = v->map.bg_c;
	while (++j < SCREENH)
	{
		if (j >= SCREENH / 2)
			color = v->map.bg_f;
		i = -1;
		while (++i < SCREENW)
			my_mlx_pixel_put(v, i, j, color);
	}
}

void	raycaster(t_var *v)
{
	int	x;

	x = -1;
	while (++x < SCREENW)
	{
		v->ray.camera_x = 2 * x / (double)SCREENW - 1;
		v->ray.ray_dir_x = v->pos.dir_x + v->pos.plane_x * v->ray.camera_x;
		v->ray.ray_dir_y = v->pos.dir_y + v->pos.plane_y * v->ray.camera_x;
		v->ray.map_x = (int)v->pos.pos_x;
		v->ray.map_y = (int)v->pos.pos_y;
		v->ray.delta_dist_x = fabs(1 / v->ray.ray_dir_x);
		v->ray.delta_dist_y = fabs(1 / v->ray.ray_dir_y);
		v->ray.hit = 0;
		get_side_dist(v);
		find_hit(v);
		get_wall_pos(v);
		put_texture_pixels(v, x);
	}
}
