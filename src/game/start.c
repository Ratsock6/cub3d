/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:48:24 by aallou-v          #+#    #+#             */
/*   Updated: 2024/05/31 11:48:03 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void ft_hook(void *param)
{
	t_core *core = param;
	
	if (mlx_is_key_down(core->mlx, MLX_KEY_RIGHT))
		rotate_player(core, ROT_SPEED);
	if (mlx_is_key_down(core->mlx, MLX_KEY_LEFT))
		rotate_player(core, -ROT_SPEED);
	if (mlx_is_key_down(core->mlx, MLX_KEY_W))
		move_foward(core);
	if (mlx_is_key_down(core->mlx, MLX_KEY_S))
		move_back(core);
	if (mlx_is_key_down(core->mlx, MLX_KEY_D))
		move_right(core);
	if (mlx_is_key_down(core->mlx, MLX_KEY_A))
		move_left(core);
	if (mlx_is_key_down(core->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(core->mlx);
	render(core);
	//start_minmap(core);
}

void	resize(int width, int height, void *param)
{
	t_core  *core;

	core = param;
	core->map->screen_height = height;
	core->map->screen_width = width;
	if (core->debug)
		printf("DEBUG WINDOWS : HEIGHT = %i WIDTH = %i\n", core->map->screen_height, core->map->screen_width);
	render(core);
}

void	start(t_core *core)
{
	t_raycast	raycast;

	raycast.image = mlx_new_image(core->mlx, core->map->screen_width, core->map->screen_height);
	core->raycast = raycast;
	mlx_set_window_limit(core->mlx, 900, 700, 1920, 1080);
	mlx_resize_hook(core->mlx, resize, core);
	mlx_loop_hook(core->mlx, ft_hook, core);
	render(core);
	//start_minmap(core);
	mlx_loop(core->mlx);
}
