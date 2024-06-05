/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:48:24 by aallou-v          #+#    #+#             */
/*   Updated: 2024/06/05 14:00:36 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	mouse_control(void *param)
{
	t_core	*core;
	int32_t	x;
	int32_t	y;

	x = 0;
	y = 0;
	core = param;
	mlx_get_mouse_pos(core->mlx, &x, &y);
	if (core->is_pause)
		return ;
	if (x > core->map->screen_width / 2 + 5)
	{
		mlx_set_mouse_pos(core->mlx, core->map->screen_width / 2,
			core->map->screen_height / 2);
		rotate_player(core, ROT_SPEED);
	}
	else if (x < core->map->screen_width / 2 - 5)
	{
		mlx_set_mouse_pos(core->mlx, core->map->screen_width / 2,
			core->map->screen_height / 2);
		rotate_player(core, -ROT_SPEED);
	}
}

void	ft_hook(void *param)
{
	t_core	*core;

	core = param;
	if (mlx_is_key_down(core->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(core->mlx);
	if (core->is_pause)
		return ;
	if (mlx_is_key_down(core->mlx, MLX_KEY_RIGHT))
		rotate_player(core, ROT_SPEED);
	if (mlx_is_key_down(core->mlx, MLX_KEY_LEFT))
		rotate_player(core, -ROT_SPEED);
	if (mlx_is_key_down(core->mlx, MLX_KEY_W))
		move_forward(core);
	if (mlx_is_key_down(core->mlx, MLX_KEY_S))
		move_back(core);
	if (mlx_is_key_down(core->mlx, MLX_KEY_D))
		move_right(core);
	if (mlx_is_key_down(core->mlx, MLX_KEY_A))
		move_left(core);
	render(core);
}

void	resize(int width, int height, void *param)
{
	t_core	*core;

	core = param;
	core->map->screen_height = height;
	core->map->screen_width = width;
	if (!core->is_pause)
		render(core);
}

void	ft_key_hook(mlx_key_data_t keys, void *param)
{
	t_core	*core;

	core = param;
	if (keys.key == MLX_KEY_F && keys.action == MLX_PRESS)
		toggle_pause(core);
}

void	start(t_core *core)
{
	t_raycast	raycast;

	core->is_pause = false;
	init_mini_map(core);
	mlx_set_cursor_mode(core->mlx, MLX_MOUSE_HIDDEN);
	mlx_set_mouse_pos(core->mlx, core->map->screen_width / 2,
		core->map->screen_height / 2);
	raycast.image = mlx_new_image(core->mlx, \
		core->map->screen_width, core->map->screen_height);
	core->raycast = raycast;
	mlx_set_window_limit(core->mlx, 900, 700, 1920, 1080);
	mlx_resize_hook(core->mlx, resize, core);
	mlx_loop_hook(core->mlx, ft_hook, core);
	mlx_loop_hook(core->mlx, mouse_control, core);
	mlx_key_hook(core->mlx, ft_key_hook, core);
	render(core);
	mlx_loop(core->mlx);
}
