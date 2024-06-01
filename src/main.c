/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 13:50:14 by aallou-v          #+#    #+#             */
/*   Updated: 2024/05/31 15:44:44 by aallou-v         ###   ########.fr       */
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

void print_texture(uint32_t *texture, int width) {
    for (int y = 0; y < 4; y++) { // print first 4 rows
        for (int x = 0; x < width; x++) {
            printf("%08x ", texture[y * width + x]);
        }
        printf("\n");
    }
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
