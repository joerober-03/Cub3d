/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joerober <joerober@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 12:25:31 by joerober          #+#    #+#             */
/*   Updated: 2023/08/22 12:25:33 by joerober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	o_checker(t_var *v, int i, int j)
{
	if (j < v->map.map_width)
		if (v->map.buffer[i][j + 1] == '0')
			return (1);
	if (j > 0)
		if (v->map.buffer[i][j - 1] == '0')
			return (1);
	if (i < v->map.map_height - 1)
		if (v->map.buffer[i + 1][j] == '0')
			return (1);
	if (i > 0)
		if (v->map.buffer[i - 1][j] == '0')
			return (1);
	return (0);
}

int	border_checker(t_var *v, int i, int j)
{
	while (++i < v->map.map_height - 1)
	{
		j = -1;
		while (++j < v->map.map_width)
			if (v->map.buffer[i][j] == ' ')
				if (o_checker(v, i, j))
					return (1);
	}
	j = -1;
	while (++j < v->map.map_width)
		if (v->map.buffer[0][j] == '0')
			return (1);
	j = -1;
	while (++j < v->map.map_width)
		if (v->map.buffer[v->map.map_height - 1][j] == '0')
			return (1);
	i = -1;
	while (++i < v->map.map_height - 1)
		if (v->map.buffer[i][0] == '0')
			return (1);
	i = -1;
	while (++i < v->map.map_height - 1)
		if (v->map.buffer[i][v->map.map_width] == '0')
			return (1);
	return (0);
}

int	player_pos_init(t_var *v, int i, int j, double a)
{
	v->pos.pos_x = i + 0.5;
	v->pos.pos_y = j + 0.5;
	v->map.map[i][j++] = 0;
	change_dir(v, a);
	return (1);
}

int	init_map_short(t_var *v, int i, int j, int p)
{
	v->map.map[i] = malloc(sizeof(int) * v->map.map_width);
	malloc_short(v, v->map.map[i]);
	while (v->map.buffer[i][j] != 0)
	{
		if (v->map.buffer[i][j] == ' ')
			v->map.map[i][j++] = 3;
		else if (v->map.buffer[i][j] == '0')
			v->map.map[i][j++] = 0;
		else if (v->map.buffer[i][j] == '1')
			v->map.map[i][j++] = 1;
		else if (v->map.buffer[i][j] == 'N')
			p += player_pos_init(v, i, j++, 0);
		else if (v->map.buffer[i][j] == 'S')
			p += player_pos_init(v, i, j++, M_PI);
		else if (v->map.buffer[i][j] == 'W')
			p += player_pos_init(v, i, j++, M_PI / 2);
		else if (v->map.buffer[i][j] == 'E')
			p += player_pos_init(v, i, j++, 1.5 * M_PI);
		else
			ft_error(v, "invalid character in map\n");
	}
	if (j < v->map.map_width)
		while (j != v->map.map_width)
			v->map.map[i][j++] = 3;
	return (p);
}

void	init_map(t_var *v)
{
	int	i;
	int	p;

	v->map.map = malloc(sizeof(int *) * v->map.map_height);
	if (v->map.map == NULL)
		ft_error(v, "malloc error\n");
	i = -1;
	p = 0;
	while (++i < v->map.map_height)
		p += init_map_short(v, i, 0, 0);
	if (p < 1)
		ft_error(v, "please include a player position in map\n");
	if (p > 1)
		ft_error(v, "too many player positions in map\n");
	if (border_checker(v, -1, 0))
		ft_error(v, "hole detected in map\n");
	mfree(v->map.buffer);
}
