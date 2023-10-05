/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joerober <joerober@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 10:46:56 by joerober          #+#    #+#             */
/*   Updated: 2023/08/22 10:46:59 by joerober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_texture_pixel(t_var *v, int i, int x)
{
	v->ray.dst = v->tex[i].addr + ((int)(v->ray.tex_y) % TEXH
			* v->tex[i].size_line + v->ray.tex_x % TEXW
			* (v->tex[i].bpp / 8));
	v->ray.color = *(unsigned int *)v->ray.dst;
	my_mlx_pixel_put(v, x, v->ray.wall_y, v->ray.color);
}

void	get_side_dist(t_var *v)
{
	if (v->ray.ray_dir_x < 0)
	{
		v->ray.step_x = -1;
		v->ray.side_dist_x = (v->pos.pos_x - v->ray.map_x)
			* v->ray.delta_dist_x;
	}
	else
	{
		v->ray.step_x = 1;
		v->ray.side_dist_x = (v->ray.map_x + 1.0 - v->pos.pos_x)
			* v->ray.delta_dist_x;
	}
	if (v->ray.ray_dir_y < 0)
	{
		v->ray.step_y = -1;
		v->ray.side_dist_y = (v->pos.pos_y - v->ray.map_y)
			* v->ray.delta_dist_y;
	}
	else
	{
		v->ray.step_y = 1;
		v->ray.side_dist_y = (v->ray.map_y + 1.0 - v->pos.pos_y)
			* v->ray.delta_dist_y;
	}
}

void	find_hit(t_var *v)
{
	while (v->ray.hit == 0)
	{
		if (v->ray.side_dist_x < v->ray.side_dist_y)
		{
			v->ray.side_dist_x += v->ray.delta_dist_x;
			v->ray.map_x += v->ray.step_x;
			v->ray.side = 0;
		}
		else
		{
			v->ray.side_dist_y += v->ray.delta_dist_y;
			v->ray.map_y += v->ray.step_y;
			v->ray.side = 1;
		}
		if (v->map.map[v->ray.map_x][v->ray.map_y] > 0)
			v->ray.hit = 1;
	}
}

void	get_wall_pos(t_var *v)
{
	if (v->ray.side == 0)
		v->ray.perp_wall_dist = (v->ray.side_dist_x - v->ray.delta_dist_x);
	else
		v->ray.perp_wall_dist = (v->ray.side_dist_y - v->ray.delta_dist_y);
	v->ray.line_height = (int)(SCREENH / v->ray.perp_wall_dist);
	v->ray.draw_start = -v->ray.line_height / 2 + SCREENH / 2;
	if (v->ray.draw_start < 0)
		v->ray.draw_start = 0;
	v->ray.draw_end = v->ray.line_height / 2 + SCREENH / 2;
	if (v->ray.draw_end >= SCREENH)
		v->ray.draw_end = SCREENH - 1;
	if (v->ray.side == 0)
		v->ray.wall_x = v->pos.pos_y + v->ray.perp_wall_dist
			* v->ray.ray_dir_y;
	else
		v->ray.wall_x = v->pos.pos_x + v->ray.perp_wall_dist
			* v->ray.ray_dir_x;
	v->ray.wall_x -= floor((v->ray.wall_x));
}

void	put_texture_pixels(t_var *v, int x)
{
	v->ray.tex_x = (int)(v->ray.wall_x * (double)TEXW);
	if (v->ray.side == 0 && v->ray.ray_dir_x > 0)
		v->ray.tex_x = TEXW - v->ray.tex_x - 1;
	if (v->ray.side == 1 && v->ray.ray_dir_y < 0)
		v->ray.tex_x = TEXW - v->ray.tex_x - 1;
	v->ray.tex_y = 0;
	v->ray.tex_y_step = TEXH / (double)v->ray.line_height;
	if (v->ray.line_height > SCREENH)
		v->ray.tex_y = (v->ray.line_height - SCREENH)
			* v->ray.tex_y_step / 2;
	v->ray.wall_y = v->ray.draw_start;
	while (v->ray.wall_y <= v->ray.draw_end)
	{
		if (v->ray.side == 0 && v->ray.step_x == -1)
			init_texture_pixel(v, 0, x);
		else if (v->ray.side == 0 && v->ray.step_x == 1)
			init_texture_pixel(v, 1, x);
		else if (v->ray.side == 1 && v->ray.step_y == -1)
			init_texture_pixel(v, 2, x);
		else if (v->ray.side == 1 && v->ray.step_y == 1)
			init_texture_pixel(v, 3, x);
		v->ray.wall_y++;
		v->ray.tex_y += v->ray.tex_y_step;
	}
}
