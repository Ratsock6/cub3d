/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 12:37:08 by aallou-v          #+#    #+#             */
/*   Updated: 2024/05/23 10:20:22 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	move_foward(t_core *core)
{
	float	new_pos_x;
	float	new_pos_y;

	ft_putendl_fd("MOVING FORWARD", 1);
	new_pos_x = core->player->pos_x;
	new_pos_y = core->player->pos_y;
	new_pos_x += cos(core->player->direction) * PLAYER_SPEED;
	if (!is_wall(core, new_pos_y, new_pos_x))
		core->player->pos_x = new_pos_x;
	new_pos_y += sin(core->player->direction) * PLAYER_SPEED;
	if (!is_wall(core, new_pos_y, new_pos_x))
		core->player->pos_y = new_pos_y;
}


void	move_back(t_core *core)
{
	float	new_pos_x;
	float	new_pos_y;

	ft_putendl_fd("MOVING BACK", 1);
	new_pos_x = core->player->pos_x;
	new_pos_y = core->player->pos_y;
	new_pos_x -= cos(core->player->direction) * PLAYER_SPEED;
	if (!is_wall(core, new_pos_y, new_pos_x))
		core->player->pos_x = new_pos_x;
	new_pos_y -= sin(core->player->direction) * PLAYER_SPEED;
	if (!is_wall(core, new_pos_y, new_pos_x))
		core->player->pos_y = new_pos_y;
}


void	move_right(t_core *core)
{
	float	new_pos_x;
	float	new_pos_y;

	ft_putendl_fd("MOVING RIGHT", 1);
	new_pos_x = core->player->pos_x;
	new_pos_y = core->player->pos_y;
	new_pos_x -= cos(core->player->direction - PI/2) * PLAYER_SPEED;
	if (!is_wall(core, new_pos_y, new_pos_x))
		core->player->pos_x = new_pos_x;
	new_pos_y -= sin(core->player->direction - PI/2) * PLAYER_SPEED;
	if (!is_wall(core, new_pos_y, new_pos_x))
		core->player->pos_y = new_pos_y;
}

void	move_left(t_core *core)
{
	float	new_pos_x;
	float	new_pos_y;

	ft_putendl_fd("MOVING LEFT", 1);
	new_pos_x = core->player->pos_x;
	new_pos_y = core->player->pos_y;
	new_pos_x += cos(core->player->direction - PI/2) * PLAYER_SPEED;
	if (!is_wall(core, new_pos_y, new_pos_x))
		core->player->pos_x = new_pos_x;
	new_pos_y += sin(core->player->direction - PI/2) * PLAYER_SPEED;
	if (!is_wall(core, new_pos_y, new_pos_x))
		core->player->pos_y = new_pos_y;
}
