/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joerober <joerober@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 10:45:46 by joerober          #+#    #+#             */
/*   Updated: 2023/08/21 15:05:15 by dferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

void	load_textures_short(t_var *v, int id, int i, char *line)
{
	char	*path;
	int		j;

	j = 0;
	i += 3;
	while (line[i] == ' ')
		i++;
	path = malloc(sizeof(char) * (ft_strlen(&line[i]) + 5));
	if (path == NULL)
		ft_error(v, "malloc error\n");
	while (line[i] != '\0' && line[i] != '\n' && line[i] != ' ')
		path[j++] = line[i++];
	path[j] = 0;
	initiate_tex(v, path, id);
	free(path);
}

void	map_dimensions_init(t_var *v, char *line, int i)
{
	if (line[i] == '0' || line[i] == '1')
	{
		if (v->map.is_c == 0 || v->map.is_f == 0 || v->tex[0].is_init == 0
			|| v->tex[1].is_init == 0 || v->tex[2].is_init == 0
			|| v->tex[3].is_init == 0)
			ft_error(v, "one or more argument missing in map\n");
		else
		{
			v->map.len = ft_strlen(line);
			if (v->map.len > v->map.map_width)
			{
				v->map.map_width = v->map.len;
				if (line[v->map.map_width - 1] == '\n')
					v->map.map_width--;
			}
			v->map.map_height++;
		}
	}
}

void	textures_parsing(t_var *v, char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == 'N' && line[i + 1] == 'O' && line[i + 2] == ' ')
		load_textures_short(v, 0, i, line);
	if (line[i] == 'S' && line[i + 1] == 'O' && line[i + 2] == ' ')
		load_textures_short(v, 1, i, line);
	if (line[i] == 'W' && line[i + 1] == 'E' && line[i + 2] == ' ')
		load_textures_short(v, 2, i, line);
	if (line[i] == 'E' && line[i + 1] == 'A' && line[i + 2] == ' ')
		load_textures_short(v, 3, i, line);
	if (line[i] == 'F' && line[i + 1] == ' ')
		bg_color_init(v, 'F', i, line);
	if (line[i] == 'C' && line[i + 1] == ' ')
		bg_color_init(v, 'C', i, line);
	map_dimensions_init(v, line, i);
}

void	load_textures(t_var *v, char *map)
{
	int		fd;
	char	*line;

	fd = open(map, O_RDONLY);
	if (fd == -1)
		ft_error(v, "please enter a valid map\n");
	line = get_next_line(fd);
	if (line == NULL)
		ft_error(v, "empty file\n");
	v->map.map_width = ft_strlen(line);
	if (line[v->map.map_width - 1] == '\n')
		v->map.map_width--;
	while (line != NULL)
	{
		textures_parsing(v, line);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	if (close(fd) == -1)
		ft_error(v, "error closing file\n");
	v->map.buffer = ft_calloc(sizeof(char *), v->map.map_height + 10);
	if (v->map.buffer == NULL)
		ft_error(v, "malloc error\n");
	init_map_buffer(v, map, 0);
}
