/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 11:24:43 by aallou-v          #+#    #+#             */
/*   Updated: 2024/05/21 17:20:35 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	init_wall(t_core *core)
{
	core->img->min_map_cube = mlx_new_image(core->mlx, SIZE_CUBE, SIZE_CUBE);
	mlx_fill_image(core->img->min_map_cube, 255, 255, 0);
}

static void	init_player(t_core *core)
{
	unsigned int	i;
	unsigned int	x;

	core->img->min_map_player = mlx_new_image(core->mlx, 10, 10);
	i = 0;
	while (i <= 2)
	{
		x = 0;
		while (x <= 2)
		{
			mlx_put_pixel(core->img->min_map_player, i, x, ft_pixel(255, 0, 0, 255));
			x++;
		}
		i++;
	}
	mlx_put_pixel(core->img->min_map_player, 1, 3, ft_pixel(255, 0, 0, 255));
	mlx_put_pixel(core->img->min_map_player, 1, 4, ft_pixel(255, 0, 0, 255));
	mlx_put_pixel(core->img->min_map_player, 1, 5, ft_pixel(255, 0, 0, 255));
	mlx_put_pixel(core->img->min_map_player, 1, 6, ft_pixel(255, 0, 0, 255));
	mlx_put_pixel(core->img->min_map_player, 1, 7, ft_pixel(255, 0, 0, 255));
}

static void	init_floor(t_core *core)
{
	core->img->min_map_floor = mlx_new_image(core->mlx, SIZE_CUBE, SIZE_CUBE);
	mlx_fill_image(core->img->min_map_floor, 0, 0, 0);
}

static mlx_image_t	*load_image(mlx_t *mlx, char *path)
{
	mlx_texture_t	*texture;
	mlx_image_t		*result;

	texture = mlx_load_png(path);
	free(path);
	if (texture == NULL)
		return (NULL);
	result = mlx_texture_to_image(mlx, texture);
	mlx_delete_texture(texture);
	return (result);
}

int	init_texture(t_core *core)
{
	core->mlx = mlx_init(SIZE_WIDTH, SIZE_HEIGHT, "CUB3D", true);
	if (core->mlx == NULL)
		return (ft_puterror("Error MLX init"));
	core->img->img_north = load_image(core->mlx, core->img->path_north);
	core->img->img_south = load_image(core->mlx, core->img->path_south);
	core->img->img_east = load_image(core->mlx, core->img->path_east);
	core->img->img_west = load_image(core->mlx, core->img->path_west);
	init_player(core);
	init_wall(core);
	init_floor(core);
	if (core->img->img_north == NULL || core->img->img_south == NULL
		|| core->img->img_east == NULL || core->img->img_west == NULL)
		return (ft_puterror("Image not load"));
	if (core->img->min_map_cube == NULL || core->img->min_map_player == NULL)
		return (ft_puterror("Player or Wall not load"));
	return (0);
}
