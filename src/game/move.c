/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 12:37:08 by aallou-v          #+#    #+#             */
/*   Updated: 2024/05/31 11:45:37 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	move_foward(t_core *core)
{
	if (core->map->map[(int) core->player->pos_y][(int) (core->player->pos_x \
		+ core->player->dirX * PLAYER_SPEED)] == '0')
		core->player->pos_x += core->player->dirX * PLAYER_SPEED;
	if (core->map->map[(int) (core->player->pos_y + core->player->dirY \
		* PLAYER_SPEED)][(int) core->player->pos_x] == '0')
		core->player->pos_y += core->player->dirY * PLAYER_SPEED;
}


void	move_back(t_core *core)
{
	if (core->map->map[(int) core->player->pos_y][(int) (core->player->pos_x \
		- core->player->dirX * PLAYER_SPEED)] == '0')
		core->player->pos_x -= core->player->dirX * PLAYER_SPEED;
	if (core->map->map[(int) (core->player->pos_y - core->player->dirY \
		* PLAYER_SPEED)][(int) core->player->pos_x] == '0')
		core->player->pos_y -= core->player->dirY * PLAYER_SPEED;
}


void	move_right(t_core *core)
{
	(void) core;
}

void	move_left(t_core *core)
{
	(void) core;
}

void	rotate_player(t_core *core, double angle)
{
	double	oldDirX;
	double	oldPlaneX;

	oldDirX = core->player->dirX;
	core->player->dirX = core->player->dirX * cos(angle) \
		- core->player->dirY * sin(angle);
	core->player->dirY = oldDirX * sin(angle) + core->player->dirY * cos(angle);
	
	oldPlaneX = core->player->planeX;
	core->player->planeX = core->player->planeX * \
		cos(angle) - core->player->planeY * sin(angle);
	core->player->planeY = oldPlaneX * sin(angle) + \
		core->player->planeY * cos(angle);
	//printf("NEW DIRECTION : PLAYE Y = %f     PLANE X = %f\n", core->player->planeY, core->player->planeX);
}
