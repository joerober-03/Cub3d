/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_buffer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joerober <joerober@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 12:25:21 by joerober          #+#    #+#             */
/*   Updated: 2023/08/22 12:25:23 by joerober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

void	malloc_short(t_var *v, int *map)
{
	if (map == NULL)
		ft_error(v, "malloc error\n");
}

int	fill_map_check(t_var *v, char *line)
{
	int	i;

	i = 0;
	if (line == NULL)
	{
		return (1);
	}
	while (line[i] == ' ')
		i++;
	if (line[i] == 'N' || line[i] == 'E' || line[i] == 'S' || line[i] == 'W')
	{
		free(line);
		ft_error(v, "hole in the wall detected\n");
	}
	if (line[i] != '0' && line[i] != '1')
	{
		free(line);
		ft_error(v, "invalid character in map\n");
	}
	return (0);
}

void	fill_map(t_var *v, char *line, int fd, int k)
{
	int	i;
	int	j;

	while (k < v->map.map_height)
	{
		i = 0;
		j = 0;
		v->map.buffer[k] = malloc(sizeof(char) * (v->map.map_width + 1));
		if (v->map.buffer[k] == NULL)
			ft_error(v, "malloc error\n");
		while (line[i] != '\n' && line[i] != 0)
			v->map.buffer[k][j++] = line[i++];
		if (j < v->map.map_width)
			while (j < v->map.map_width)
				v->map.buffer[k][j++] = ' ';
		v->map.buffer[k++][j] = 0;
		free(line);
		line = get_next_line(fd);
		if (k == v->map.map_height || fill_map_check(v, line) == 1)
		{
			free(line);
			break ;
		}
	}
}

void	init_map_buffer(t_var *v, char *map, int i)
{
	int		fd;
	char	*line;

	if (v->map.is_c == 0 || v->map.is_f == 0 || v->tex[0].is_init == 0
		|| v->tex[1].is_init == 0 || v->tex[2].is_init == 0
		|| v->tex[3].is_init == 0 || v->map.map_height == 0)
		ft_error(v, "one or more argument missing in map\n");
	fd = open(map, O_RDONLY);
	if (fd == -1)
		ft_error(v, "please enter a valid map\n");
	line = get_next_line(fd);
	while (line != NULL)
	{
		i = 0;
		while (line[i] == ' ')
			i++;
		if (line[i] == '0' || line[i] == '1')
			break ;
		free(line);
		line = get_next_line(fd);
	}
	fill_map(v, line, fd, 0);
	if (close(fd) == -1)
		ft_error(v, "error closing file\n");
	init_map(v);
}
