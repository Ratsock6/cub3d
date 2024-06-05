/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxborde <maxborde@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 13:05:39 by maxborde          #+#    #+#             */
/*   Updated: 2024/06/05 13:06:58 by maxborde         ###   ########.fr       */
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
