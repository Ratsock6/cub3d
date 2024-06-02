/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 12:37:08 by aallou-v          #+#    #+#             */
/*   Updated: 2024/06/01 22:34:03 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	perform_move_x(t_core *core, double move_x, double new_pos_x)
{
	if (move_x > 0)
	{
		if (core->map->map[(int)core->player->pos_y][(int)(new_pos_x + PLAYER_BUFFER)] == '0')
		{
			core->player->pos_x = new_pos_x;
		}
	}
	else
	{
		if (core->map->map[(int)core->player->pos_y][(int)(new_pos_x - PLAYER_BUFFER)] == '0')
		{
			core->player->pos_x = new_pos_x;
		}
	}
}

void	perform_move_y(t_core *core, double move_y, double new_pos_y)
{
	if (move_y > 0)
	{
		if (core->map->map[(int)(new_pos_y + PLAYER_BUFFER)][(int)core->player->pos_x] == '0')
		{
			core->player->pos_y = new_pos_y;
		}
	}
	else
	{
		if (core->map->map[(int)(new_pos_y - PLAYER_BUFFER)][(int)core->player->pos_x] == '0')
		{
			core->player->pos_y = new_pos_y;
		}
	}
}

void	move_forward(t_core *core)
{
	double	new_pos_x;
	double	new_pos_y;
	double	move_x;
	double	move_y;

	move_x = core->player->dir_x * PLAYER_SPEED;
	move_y = core->player->dir_y * PLAYER_SPEED;
	new_pos_x = core->player->pos_x + move_x;
	new_pos_y = core->player->pos_y + move_y;

	perform_move_x(core, move_x, new_pos_x);
	perform_move_y(core, move_y, new_pos_y);
}

void	move_back(t_core *core)
{
	double	new_pos_x;
	double	new_pos_y;
	double	move_x;
	double	move_y;

	move_x = -core->player->dir_x * PLAYER_SPEED;
	move_y = -core->player->dir_y * PLAYER_SPEED;
	new_pos_x = core->player->pos_x + move_x;
	new_pos_y = core->player->pos_y + move_y;

	perform_move_x(core, move_x, new_pos_x);
	perform_move_y(core, move_y, new_pos_y);
}

void	move_right(t_core *core)
{
	double	new_pos_x;
	double	new_pos_y;
	double	move_x;
	double	move_y;

	move_x = core->player->plane_x * PLAYER_SPEED;
	move_y = core->player->plane_y * PLAYER_SPEED;
	new_pos_x = core->player->pos_x + move_x;
	new_pos_y = core->player->pos_y + move_y;

	perform_move_x(core, move_x, new_pos_x);
	perform_move_y(core, move_y, new_pos_y);
}

void	move_left(t_core *core)
{
	double	new_pos_x;
	double	new_pos_y;
	double	move_x;
	double	move_y;

	move_x = -core->player->plane_x * PLAYER_SPEED;
	move_y = -core->player->plane_y * PLAYER_SPEED;
	new_pos_x = core->player->pos_x + move_x;
	new_pos_y = core->player->pos_y + move_y;

	perform_move_x(core, move_x, new_pos_x);
	perform_move_y(core, move_y, new_pos_y);
}

void	rotate_player(t_core *core, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = core->player->dir_x;
	core->player->dir_x = core->player->dir_x * cos(angle) - core->player->dir_y * sin(angle);
	core->player->dir_y = old_dir_x * sin(angle) + core->player->dir_y * cos(angle);
	old_plane_x = core->player->plane_x;
	core->player->plane_x = core->player->plane_x * cos(angle) - core->player->plane_y * sin(angle);
	core->player->plane_y = old_plane_x * sin(angle) + core->player->plane_y * cos(angle);
}
