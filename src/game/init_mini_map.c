/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mini_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 18:35:53 by aallou-v          #+#    #+#             */
/*   Updated: 2024/06/02 18:41:57 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	inside_init(t_core *core, size_t x, size_t y)
{
	if (core->map->map[y][x] == '1')
	{
		mlx_image_to_window(core->mlx, core->img->min_map_cube, \
			x * SIZE_CUBE, y * SIZE_CUBE);
		core->img->min_map_cube->instances[core->img->wall_count]
			.enabled = false;
		core->img->wall_count++;
	}
	if (core->map->map[y][x] == '0' || core->map->map[y][x] == ' ')
	{
		mlx_image_to_window(core->mlx, core->img->min_map_floor, \
			x * SIZE_CUBE, y * SIZE_CUBE);
		core->img->min_map_floor->instances[core->img->floor_count]
			.enabled = false;
		core->img->floor_count++;
	}
}

void	init_mini_map(t_core *core)
{
	size_t	y;
	size_t	x;

	y = -1;
	core->img->wall_count = 0;
	core->img->floor_count = 0;
	while (++y <= core->map->height)
	{
		x = -1;
		while (++x <= core->map->width)
		{
			if (x >= ft_strlen(core->map->map[y]))
			{
				mlx_image_to_window(core->mlx, core->img->min_map_floor, \
					x * SIZE_CUBE, y * SIZE_CUBE);
				core->img->min_map_floor->instances[core->img->floor_count]
					.enabled = false;
				core->img->floor_count++;
				continue ;
			}
			inside_init(core, x, y);
		}
	}
}
