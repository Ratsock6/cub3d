/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 13:50:14 by aallou-v          #+#    #+#             */
/*   Updated: 2024/05/14 17:24:30 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_all(t_core *core)
{
	free_str_tab(core->map->map);
	free(core->map);
	free(core->img->path_north);
	free(core->img->path_south);
	free(core->img->path_east);
	free(core->img->path_west);
	free(core->img->floor);
	free(core->img->celling);
	free(core->img);
}

int	main(int argc, char **argv)
{
	t_core	core;

	if (check_error(argc, argv))
		return (1);
	if (init(&core, argv))
	{
		free_all(&core);
		return(1);
	}
	printf("%s\n", core.img->path_north);
	printf("%s\n", core.img->path_south);
	printf("%s\n", core.img->path_west);
	printf("%s\n", core.img->path_east);
	printf("R : %i G : %i B : %i\n", core.img->floor->r, core.img->floor->g, core.img->floor->b);
	printf("R : %i G : %i B : %i\n", core.img->celling->r, core.img->celling->g, core.img->celling->b);
	free_all(&core);
	return (0);
}
