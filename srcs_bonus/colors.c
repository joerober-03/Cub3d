/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joerober <joerober@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 12:19:26 by joerober          #+#    #+#             */
/*   Updated: 2023/08/22 12:19:29 by joerober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned long	create_rgb(int r, int g, int b)
{
	return (((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff));
}

int	bg_color_init_atoi(t_var *v, int i, char *line)
{
	int		j;
	int		res;
	char	*buffer;

	buffer = malloc(sizeof(char) * (sizeof(line) + 1));
	if (buffer == NULL)
		ft_error(v, "malloc error\n");
	j = 0;
	while (line[i] != ',' && line[i] != '\n' && line[i] != 0 && line[i] != ' ')
	{
		if (line[i] < 48 || line[i] > 57)
			ft_error(v, "invalid color\n");
		buffer[j++] = line[i++];
	}
	if (j == 0)
		ft_error(v, "invalid color\n");
	buffer[j] = 0;
	res = ft_atoi(buffer);
	if (res > 255 || res < 0)
		ft_error(v, "invalid color\n");
	free(buffer);
	return (res);
}

int	bg_color_init_short(char *line, int i)
{
	while (line[i] == ' ')
		i++;
	while (line[i] != ',' && line[i] != '\n')
		i++;
	i++;
	while (line[i] == ' ')
		i++;
	return (i);
}

void	bg_color_init(t_var *v, char c, int i, char *line)
{
	int	int1;
	int	int2;
	int	int3;

	i += 2;
	while (line[i] == ' ')
		i++;
	int1 = bg_color_init_atoi(v, i, line);
	i = bg_color_init_short(line, i);
	int2 = bg_color_init_atoi(v, i, line);
	i = bg_color_init_short(line, i);
	int3 = bg_color_init_atoi(v, i, line);
	if (c == 'C')
	{
		v->map.bg_c = create_rgb(int1, int2, int3);
		v->map.is_c++;
	}
	else
	{
		v->map.bg_f = create_rgb(int1, int2, int3);
		v->map.is_f++;
	}
	if (v->map.is_f > 1 || v->map.is_c > 1)
		ft_error(v, "duplicate color informations\n");
}
