/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 11:24:43 by aallou-v          #+#    #+#             */
/*   Updated: 2024/06/01 20:17:20 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <stdint.h>

static void	init_wall(t_core *core)
{
	core->img->min_map_cube = mlx_new_image(core->mlx, SIZE_CUBE, SIZE_CUBE);
	mlx_fill_image(core->img->min_map_cube, 255, 255, 0);
}

static void	init_player(t_core *core)
{
	core->img->min_map_player = mlx_new_image(core->mlx, 2, 2);
	mlx_fill_image(core->img->min_map_player, 255, 0, 0);
}

static void	init_floor(t_core *core)
{
	core->img->min_map_floor = mlx_new_image(core->mlx, SIZE_CUBE, SIZE_CUBE);
	mlx_fill_image(core->img->min_map_floor, 0, 0, 0);
}

uint32_t	*get_texture_map(t_core *core, char *path)
{
	uint32_t		*texture_map;
	mlx_texture_t	*texture;

	texture = mlx_load_png(path);
	free(path);
	if (texture == NULL)
		return (NULL);
	texture_map = malloc(sizeof(uint32_t) * (texture->width * texture->height));
	convert_to_hex(texture_map, texture->pixels, \
		texture->width, texture->height);
	core->img->text_height = texture->height;
	core->img->text_width = texture->width;
	printf("TEXT HEIGHT = %d\n", core->img->text_height);
	printf("TEXT WIDTH = %d\n", core->img->text_width);
	mlx_delete_texture(texture);
	return (texture_map);
}

int	init_texture(t_core *core)
{
	core->mlx = mlx_init(SIZE_WIDTH, SIZE_HEIGHT, "CUB3D", true);
	if (core->mlx == NULL)
		return (ft_puterror("Error MLX init"));
	core->img->text_map_north = get_texture_map(core, core->img->path_north);
	core->img->text_map_south = get_texture_map(core, core->img->path_south);
	core->img->text_map_east = get_texture_map(core, core->img->path_east);
	core->img->text_map_west = get_texture_map(core, core->img->path_west);
	init_player(core);
	init_wall(core);
	init_floor(core);
	if (core->img->text_map_north == NULL || core->img->text_map_south == NULL
		|| core->img->text_map_east == NULL || core->img->text_map_west == NULL)
		return (ft_puterror("img not load"));
	if (core->img->min_map_cube == NULL || core->img->min_map_player == NULL)
		return (ft_puterror("Player or Wall not load"));
	return (0);
}
