/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:06:04 by aallou-v          #+#    #+#             */
/*   Updated: 2024/06/05 13:06:42 by maxborde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../minilibx/mlx42.h"
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <math.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

# define Y 0
# define X 1
# define SIZE_HEIGHT 1000
# define SIZE_WIDTH 1900
# define SIZE_CUBE 20
# define PLAYER_SPEED 0.1
# define ROT_SPEED 0.05
# define PLAYER_BUFFER 0.1
# define FOV 90.0  // Field Of View in degrees

typedef struct s_map
{
	char		**map;
	int			fd;
	int			screen_width;
	int			screen_height;
	size_t		width;
	size_t		height;
}				t_map;

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}		t_rgb;

typedef struct s_norm_fill
{
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	double	wall_x;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
}		t_norm_fill;

typedef struct s_norm_draw
{
	int			line_height;
	int			draw_end;
	int			draw_start;
	uint32_t	*texture_map;
	int			tex_x;
	int			tex_y;
	int			dist_to_top;
	int			y;
	uint32_t	color;
}		t_norm_draw;

typedef struct s_img
{
	char			*path_north;
	uint32_t		*text_map_north;
	char			*path_south;
	uint32_t		*text_map_south;
	char			*path_east;
	uint32_t		*text_map_east;
	char			*path_west;
	uint32_t		*text_map_west;
	t_rgb			*floor;
	t_rgb			*celling;
	mlx_image_t		*min_map_player;
	mlx_image_t		*min_map_cube;
	size_t			floor_count;
	mlx_image_t		*min_map_floor;
	size_t			wall_count;
	mlx_image_t		*img_pause;
	int				text_height;
	int				text_width;
}		t_img;

typedef struct s_raycast
{
	double		x;
	double		y;
	double		dist;
	int			side; // 0 for vertical, 1 for horizontal
	double		wall_x;
	mlx_image_t	*image;
	double		ray_dir_x;
	double		ray_dir_y;
}	t_raycast;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	angle;
}				t_player;

typedef struct s_core
{
	t_map		*map;
	t_img		*img;
	mlx_t		*mlx;
	double		pos[2];
	char		**tmp_map;
	int			debug;
	t_player	*player;
	t_raycast	raycast;
	bool		is_pause;
}				t_core;

//RENDERING
void	rendering(t_core *core);
void	rendering_test(t_core *core);

//PARSING
int		check_error(int argc, char **argv);
int		init(t_core *core, char **argv);
int		parsing_data(t_core *core);
int		parsing_map(t_core *core);
int		init_texture(t_core *core);
void	pre_free_path(t_core *core);

//CHECKING
bool	is_map_closed(char **map);

// UTILS
int		ft_puterror(char *error);
size_t	ft_len_tab(char **str_tab);
int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);
void	mlx_fill_image(mlx_image_t *img, int32_t r, int32_t g, int32_t b);
void	mlx_fill_floor(mlx_image_t *img, int32_t r, int32_t g, int32_t b);
void	rgb(t_rgb *rgb, char **values);
void	convert_to_hex(uint32_t *texture_map, uint8_t *pixels, int w, int h);
void	remove_spaces(char *str);

//GAME
void	start(t_core *core);
void	render_minmap(void *param);
void	init_minmap(t_core *core);
void	render(t_core *core);
void	fill_raycast(double ray_dir_x, double ray_dir_y, t_core *core);
void	draw_column(t_core *core, int x);
void	toggle_pause(t_core *core);
void	init_mini_map(t_core *core);

//MOVE
void	move_back(t_core *core);
void	move_forward(t_core *core);
void	move_right(t_core *core);
void	move_left(t_core *core);
void	rotate_player(t_core *core, double angle);
void	perform_move_x(t_core *core, double move_x, double new_pos_x);
void	perform_move_y(t_core *core, double move_y, double new_pos_y);

#endif
