/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pause.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 16:14:54 by aallou-v          #+#    #+#             */
/*   Updated: 2024/06/02 18:36:01 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	delete_mini_map(t_core *core)
{
	size_t	floor_count;
	size_t	wall_count;

	floor_count = -1;
	while (++floor_count <= core->img->floor_count)
	{
		core->img->min_map_floor->instances[floor_count].enabled = false;
	}
	wall_count = -1;
	while (++wall_count <= core->img->wall_count)
	{
		core->img->min_map_cube->instances[wall_count].enabled = false;
	}
}

static void	show_mini_map(t_core *core)
{
	size_t	floor_count;
	size_t	wall_count;

	floor_count = -1;
	while (++floor_count <= core->img->floor_count)
	{
		core->img->min_map_floor->instances[floor_count].enabled = true;
	}
	wall_count = -1;
	while (++wall_count <= core->img->wall_count)
	{
		core->img->min_map_cube->instances[wall_count].enabled = true;
	}
}

static void	game_pause(t_core *core)
{
	core->raycast.image->instances[0].enabled = false;
	core->img->img_pause->instances[0].enabled = true;
	core->img->img_pause->instances[0].y = core->map->screen_height / 2;
	core->img->img_pause->instances[0].x = core->map->screen_width / 2;
	show_mini_map(core);
	mlx_set_cursor_mode(core->mlx, MLX_MOUSE_NORMAL);
}

static void	game_unpause(t_core *core)
{
	core->raycast.image->instances[0].enabled = true;
	core->img->img_pause->instances[0].enabled = false;
	delete_mini_map(core);
	mlx_set_cursor_mode(core->mlx, MLX_MOUSE_HIDDEN);
}

void	toggle_pause(t_core *core)
{
	core->is_pause = !core->is_pause;
	if (core->is_pause)
		game_pause(core);
	else
		game_unpause(core);
}
