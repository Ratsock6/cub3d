/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 13:50:14 by aallou-v          #+#    #+#             */
/*   Updated: 2024/06/01 20:11:18 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_all(t_core *core)
{
	free_str_tab(core->map->map);
	free(core->map);
	free(core->img->floor);
	free(core->img->celling);
	free(core->img->text_map_east);
	free(core->img->text_map_north);
	free(core->img->text_map_south);
	free(core->img->text_map_west);
	free(core->img);
	free(core->player);
	if (core->mlx)
		mlx_terminate(core->mlx);
}

int	main(int argc, char **argv)
{
	t_core	core;

	core.debug = 1;
	if (check_error(argc, argv))
		return (1);
	if (init(&core, argv))
	{
		free_all(&core);
		return (1);
	}
	start(&core);
	free_all(&core);
	return (0);
}
