/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pause.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 16:14:54 by aallou-v          #+#    #+#             */
/*   Updated: 2024/06/02 16:49:34 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	game_pause(t_core *core)
{
	core->raycast.image->instances[0].enabled = false;
	core->img->img_pause->instances[0].enabled = true;
	core->img->img_pause->instances[0].y = core->map->screen_height / 2;
	core->img->img_pause->instances[0].x = core->map->screen_width / 2;
	mlx_set_cursor_mode(core->mlx, MLX_MOUSE_NORMAL);
}

static void	game_unpause(t_core *core)
{
	core->raycast.image->instances[0].enabled = true;
	core->img->img_pause->instances[0].enabled = false;
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
