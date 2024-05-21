/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minmap_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 16:03:23 by aallou-v          #+#    #+#             */
/*   Updated: 2024/05/21 17:08:59 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void ft_hook(void *param)
{
	t_core *core = param;

	if (mlx_is_key_down(core->mlx, MLX_KEY_UP))
		core->img->min_map_player->instances[0].y -= 1;
	if (mlx_is_key_down(core->mlx, MLX_KEY_DOWN))
		core->img->min_map_player->instances[0].y += 1;
	if (mlx_is_key_down(core->mlx, MLX_KEY_LEFT))
		core->img->min_map_player->instances[0].x -= 1;
	if (mlx_is_key_down(core->mlx, MLX_KEY_RIGHT))
		core->img->min_map_player->instances[0].x += 1;
}

void	start_minmap(t_core *core)
{
	size_t	y;
	size_t	x;

	y = 0;
	printf("DEBUG = %zu\n", core->map->height);
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
	mlx_loop_hook(core->mlx, ft_hook, core);
}
