/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dferreir <dferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 15:27:45 by dferreir          #+#    #+#             */
/*   Updated: 2023/08/23 11:37:19 by dferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

void	crosshair(t_var *v)
{
	int	x;
	int	y;
	int	factor;

	factor = SCREENW / 100;
	x = SCREENW / 2 - factor - 1;
	y = SCREENH / 2;
	while (++x <= SCREENW / 2 + factor)
	{
		my_mlx_pixel_put(v, x, y + 1, 0xFF0000);
		my_mlx_pixel_put(v, x, y, 0xFF0000);
		my_mlx_pixel_put(v, x, y - 1, 0xFF0000);
	}
	x = SCREENW / 2;
	y = SCREENH / 2 - factor - 1;
	while (++y <= SCREENH / 2 + factor)
	{
		my_mlx_pixel_put(v, x + 1, y, 0xFF0000);
		my_mlx_pixel_put(v, x, y, 0xFF0000);
		my_mlx_pixel_put(v, x - 1, y, 0xFF0000);
	}
}

void	display(t_var *v)
{
	v->image.img = mlx_new_image(v->mlx, SCREENW, SCREENH);
	v->image.addr = mlx_get_data_addr(v->image.img,
			&v->image.bits_per_pixel, &v->image.line_length, &v->image.endian);
	background_display(v);
	raycaster(v);
	if (v->map.show_crosshair % 2 == 0)
		crosshair(v);
	if (v->map.show_map % 2 == 0)
		mini_map_base(v);
	mlx_put_image_to_window(v->mlx, v->mlx_win, v->image.img, 0, 0);
}

void	loop(t_var *v, char **argv)
{
	v->mlx = mlx_init();
	load_textures(v, argv[1]);
	v->mlx_win = mlx_new_window(v->mlx, -1, -1, SCREENW, SCREENH, "Ham");
	display(v);
	mlx_hook(v->mlx_win, 17, 0, close_hook, v);
	mlx_hook(v->mlx_win, 2, 0, keyhook, v);
	mlx_hook(v->mlx_win, 6, 0, mouse_move, v);
	mlx_loop(v->mlx);
}

void	values_init(t_var *v)
{
	v->pos.dir_x = -1;
	v->pos.dir_y = 0;
	v->pos.plane_x = 0;
	v->pos.plane_y = 0.66;
	v->pos.mouse_x = SCREENW / 2;
	v->map.is_c = 0;
	v->map.is_f = 0;
	v->tex[0].is_init = 0;
	v->tex[1].is_init = 0;
	v->tex[2].is_init = 0;
	v->tex[3].is_init = 0;
	v->map.map_height = 0;
	v->map.map_width = 0;
	v->map.show_map = 0;
	v->map.show_crosshair = 0;
}

int	main(int argc, char **argv)
{
	t_var	*v;

	v = (t_var *)malloc(sizeof(t_var));
	if (v == NULL)
	{
		ft_printf("malloc error\n");
		exit(1);
	}
	if (argc != 2)
		ft_error(v, "please enter the right number of arguments\n");
	values_init(v);
	loop(v, argv);
	return (0);
}
