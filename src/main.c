/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 13:50:14 by aallou-v          #+#    #+#             */
/*   Updated: 2024/05/17 16:12:35 by maxborde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_tab(char **str_tab)
{
	size_t	i;

	if (str_tab)
	{
		i = 0;
		while (str_tab[i])
		{
			ft_putendl_fd(str_tab[i], 2);
			i++;
		}
	}
}

static void	free_all(t_core *core)
{
	free_str_tab(core->map->map);
	free(core->map);
	free(core->img->floor);
	free(core->img->celling);
	free(core->img);
	if (core->mlx)
		mlx_terminate(core->mlx);
}

int	main(int argc, char **argv)
{
	t_core	core;

	if (check_error(argc, argv))
		return (1);
	if (init(&core, argv))
	{
		free_all(&core);
		return (1);
	}
	print_tab(core.map->map);
	printf("IS MAP CLOSED = %d\n", is_map_closed(core.map->map));
	//rendering(&core);
	free_all(&core);
	return (0);
}
