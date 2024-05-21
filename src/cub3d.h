/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:06:04 by aallou-v          #+#    #+#             */
/*   Updated: 2024/05/21 16:30:01 by aallou-v         ###   ########.fr       */
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
# define SIZE_CUBE 16

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

typedef enum e_states
{
	NORTH,
	SOUTH,
	EAST,
	WEST
}	t_states;

typedef struct s_texture
{
	char			*path_north;
	mlx_image_t		*img_north;
	char			*path_south;
	mlx_image_t		*img_south;
	char			*path_east;
	mlx_image_t		*img_east;
	char			*path_west;
	mlx_image_t		*img_west;
	t_rgb			*floor;
	t_rgb			*celling;
	mlx_image_t		*min_map_player;
	mlx_image_t		*min_map_cube;
	mlx_image_t		*min_map_floor;
}		t_texture;

typedef struct s_core
{
	t_map		*map;
	t_texture	*img;
	mlx_t		*mlx;
	t_states	direction;
	double		pos[2];
	char		**tmp_map;
	int			debug;
}				t_core;

//PARSING
int		check_error(int argc, char **argv);
int		init(t_core *core, char **argv);
int		parsing_data(t_core *core);
int		parsing_map(t_core *core);
int		init_texture(t_core *core);
void	pre_free_path(t_core *core);

// UTILS
int		ft_puterror(char *error);
size_t	ft_len_tab(char **str_tab);
int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);
void	mlx_fill_image(mlx_image_t *img, int32_t r, int32_t g, int32_t b);

//GAME
void	start(t_core *core);
void	start_minmap(t_core *core);

#endif