/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:06:04 by aallou-v          #+#    #+#             */
/*   Updated: 2024/05/14 17:24:48 by aallou-v         ###   ########.fr       */
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

typedef struct s_map
{
	char		**map;
	int			fd;
	int			height;
	int			weith;
}				t_map;

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}		t_rgb;

typedef struct s_texture
{
	char			*path_north;
	mlx_texture_t	*north;
	mlx_image_t		*img_north;
	char			*path_south;
	mlx_texture_t	*south;
	mlx_image_t		*img_south;
	char			*path_east;
	mlx_texture_t	*east;
	mlx_image_t		*img_east;
	char			*path_west;
	mlx_texture_t	*west;
	mlx_image_t		*img_west;
	t_rgb			*floor;
	t_rgb			*celling;
}		t_texture;

typedef struct s_core
{
	t_map		*map;
	t_texture	*img;
}				t_core;

//PARSING
int		check_error(int argc, char **argv);
int		init(t_core *core, char **argv);
int		parsing_data(t_core *core);
int		parsing_map(t_core *core);

// UTILS
int		ft_puterror(char *error);
size_t  ft_len_tab(char **str_tab);

#endif