/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minmap_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 16:03:23 by aallou-v          #+#    #+#             */
/*   Updated: 2024/05/31 11:47:52 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_minmap(t_core *core)
{
	(void) core;
}

void	render_minmap(t_core *core)
{
	size_t	y;
	size_t	x;

	y = 0;
	while (y <= core->map->height)
	{
		x = 0;
		while (x < ft_strlen(core->map->map[y]))
		{
			if (core->map->map[y][x] == '1')
				mlx_image_to_window(core->mlx, core->img->min_map_cube, x * SIZE_CUBE, y * SIZE_CUBE);
			if (core->map->map[y][x] == '0')
				mlx_image_to_window(core->mlx, core->img->min_map_floor, x * SIZE_CUBE, y * SIZE_CUBE);
			x++;
		}
		y++;
	}
	mlx_image_to_window(core->mlx, core->img->min_map_player, core->player->pos_x * SIZE_CUBE, core->player->pos_y * SIZE_CUBE);
}
