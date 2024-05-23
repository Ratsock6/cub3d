/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_wall.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:09:57 by aallou-v          #+#    #+#             */
/*   Updated: 2024/05/22 15:47:12 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	is_wall(t_core *core, float pos_y, float pos_x)
{
	int	x;
	int	y;

	x = (int)pos_x;
	y = (int)pos_y;
	if (x < 0 || y < 0 || x >= (int)core->map->width
		|| y >= (int)core->map->height)
		return (1);
	return (core->map->map[y][x] == '1');
}
