/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 13:50:14 by aallou-v          #+#    #+#             */
/*   Updated: 2024/05/13 19:05:04 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_all(t_core *core)
{
	free_str_tab(core->map->map);
	free(core->map);
}

int	main(int argc, char **argv)
{
	t_core	core;

	if (init(&core) || check_error(argc, argv, &core))
	{
		free_all(&core);
		return(1);
	}
	return (0);
}
