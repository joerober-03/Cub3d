/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dferreir <dferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 15:25:05 by dferreir          #+#    #+#             */
/*   Updated: 2023/08/22 11:40:36 by dferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <math.h>
# include <fcntl.h>
# include "../libmlx/includes/mlx.h"
# include "../libft/libft.h"

# define SCREENW 1450
# define SCREENH 1000
# define TEXW 64
# define TEXH 64

typedef struct s_tex
{
	void	*ptr;
	char	*addr;
	int		bpp;
	int		size_line;
	int		endian;
	int		is_init;
}				t_tex;

typedef struct s_ray
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
	double	wall_x;
	int		tex_x;
	double	tex_y;
	double	tex_y_step;
	int		wall_y;
	int		hit;
	int		color;
	char	*dst;
}				t_ray;

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_image;

typedef struct s_pos
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	int		mouse_x;
}				t_pos;

typedef struct s_map
{
	int		show_map;
	int		show_crosshair;
	int		bg_c;
	int		bg_f;
	int		is_c;
	int		is_f;
	int		**map;
	char	**buffer;
	int		map_height;
	int		map_width;
	int		initial_x;
	int		initial_y;
	int		not_closed;
	int		acc;
	int		index_x;
	int		index_y;
	int		total_x;
	int		total_y;
	int		len;
}				t_map;

typedef struct s_var
{
	t_image	image;
	t_pos	pos;
	t_tex	tex[4];
	t_ray	ray;
	t_map	map;
	void	*mlx;
	void	*mlx_win;
}				t_var;

//graphics
void			background_display(t_var *v);
void			my_mlx_pixel_put(t_var *v, int x, int y, int color);
void			raycaster(t_var *v);

//hooks
int				close_hook(int button, t_var *v);
int				keyhook(int keycode, t_var *v);
int				mouse_move(int x, int y, t_var *v);
void			display(t_var *v);

//parser
void			load_textures(t_var *v, char *map);

//mini_map
void			mini_map_base(t_var *var);

//raycaster_utils
void			init_texture_pixel(t_var *v, int i, int x);
void			get_side_dist(t_var *v);
void			find_hit(t_var *v);
void			get_wall_pos(t_var *v);
void			put_texture_pixels(t_var *v, int x);
void			put_texture_pixels_short(t_var *v, int x);

//colors

unsigned long	create_rgb(int r, int g, int b);
void			bg_color_init(t_var *v, char c, int i, char *line);

//map

void			init_map(t_var *v);
void			malloc_short(t_var *v, int *map);

//map_buffer

void			init_map_buffer(t_var *v, char *map, int i);

//utils
void			ft_error(t_var *v, char *error);
void			initiate_tex(t_var *v, char *path, int i);
void			change_dir(t_var *v, double multiplier);
char			**mfree(char **tab);

#endif
