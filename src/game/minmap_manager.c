/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minmap_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 16:03:23 by aallou-v          #+#    #+#             */
/*   Updated: 2024/05/29 14:35:34 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_key_hook(mlx_key_data_t keydata, void *param)
{
	t_core	*core;

	core = param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(core->mlx);
	if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
		core->player->direction = core->player->direction + ROTATION_SPEED;
	if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
		core->player->direction = core->player->direction - ROTATION_SPEED;
}

void ft_hook(void *param)
{
	t_core *core = param;

	if (mlx_is_key_down(core->mlx, MLX_KEY_W))
		move_foward(core);
	if (mlx_is_key_down(core->mlx, MLX_KEY_S))
		move_back(core);
	if (mlx_is_key_down(core->mlx, MLX_KEY_A))
		move_left(core);
	if (mlx_is_key_down(core->mlx, MLX_KEY_D))
		move_right(core);
	core->img->min_map_player->instances[0].x = core->player->pos_x * SIZE_CUBE;
	core->img->min_map_player->instances[0].y = core->player->pos_y * SIZE_CUBE;
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
	mlx_key_hook(core->mlx, ft_key_hook, core);
}
