/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 12:37:08 by aallou-v          #+#    #+#             */
/*   Updated: 2024/05/31 15:51:22 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	move_foward(t_core *core)
{
	if (core->map->map[(int) core->player->pos_y][(int)(core->player->pos_x \
		+ core->player->dir_x * PLAYER_SPEED)] == '0')
		core->player->pos_x += core->player->dir_x * PLAYER_SPEED;
	if (core->map->map[(int)(core->player->pos_y + core->player->dir_y \
		* PLAYER_SPEED)][(int) core->player->pos_x] == '0')
		core->player->pos_y += core->player->dir_y * PLAYER_SPEED;
}

void	move_back(t_core *core)
{
	if (core->map->map[(int) core->player->pos_y][(int)(core->player->pos_x \
		- core->player->dir_x * PLAYER_SPEED)] == '0')
		core->player->pos_x -= core->player->dir_x * PLAYER_SPEED;
	if (core->map->map[(int)(core->player->pos_y - core->player->dir_y \
		* PLAYER_SPEED)][(int) core->player->pos_x] == '0')
		core->player->pos_y -= core->player->dir_y * PLAYER_SPEED;
}

void	move_right(t_core *core)
{
	(void) core;
}

void	move_left(t_core *core)
{
	core->player->pos_x += core->player->dir_x * PLAYER_SPEED;
	(void) core;
}

void	rotate_player(t_core *core, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = core->player->dir_x;
	core->player->dir_x = core->player->dir_x * cos(angle) \
		- core->player->dir_y * sin(angle);
	core->player->dir_y = old_dir_x * sin(angle) + core->player->dir_y \
		* cos(angle);
	old_plane_x = core->player->plane_x;
	core->player->plane_x = core->player->plane_x * \
		cos(angle) - core->player->plane_y * sin(angle);
	core->player->plane_y = old_plane_x * sin(angle) + \
		core->player->plane_y * cos(angle);
}
