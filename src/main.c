/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 13:50:14 by aallou-v          #+#    #+#             */
/*   Updated: 2024/05/30 20:16:51 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_all(t_core *core)
{
	free_str_tab(core->map->map);
	free(core->map);
	free(core->img->floor);
	free(core->img->celling);
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
	//printf("C %i, %i, %i\n", core.img->celling->r, core.img->celling->g, core.img->celling->b);
	start(&core);
	free_all(&core);
	return (0);
}
