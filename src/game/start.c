/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:48:24 by aallou-v          #+#    #+#             */
/*   Updated: 2024/05/30 17:32:41 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	resize(int width, int height, void *param)
{
	t_core  *core;

	core = param;
	core->map->screen_height = height;
	core->map->screen_width = width;
	if (core->debug)
		printf("DEBUG WINDOWS : HEIGHT = %i WIDTH = %i\n", core->map->screen_height, core->map->screen_width);
}

void	start(t_core *core)
{
	mlx_set_window_limit(core->mlx, 900, 700, 1920, 1080);
	mlx_resize_hook(core->mlx, resize, core);
	render(core);
	//start_minmap(core);
	mlx_loop(core->mlx);
}