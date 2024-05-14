/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 18:24:39 by aallou-v          #+#    #+#             */
/*   Updated: 2024/05/14 17:42:08 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	init_path_null(t_core *core)
{
	core->img->path_east = NULL;
	core->img->path_north = NULL;
	core->img->path_south = NULL;
	core->img->path_west = NULL;
}

static int	open_file(t_core *core, char **argv)
{
	core->map->fd = open(argv[1], O_RDONLY);
	if (core->map->fd <= 0)
		return (1);
	return (0);
}

static int	data_error(t_core *core)
{
	if (core->img->path_east == NULL)
		return (ft_puterror("East texture not initialise"));
	if (core->img->path_north == NULL)
		return (ft_puterror("North texture not initialise"));
	if (core->img->path_south == NULL)
		return (ft_puterror("South texture not initialise"));
	if (core->img->path_west == NULL)
		return (ft_puterror("West texture not initialise"));
	if ((core->img->floor->r > 255 || core->img->floor->r < 0)
		|| (core->img->floor->g > 255 || core->img->floor->g < 0)
		|| (core->img->floor->b > 255 || core->img->floor->b < 0)
	)
		return (ft_puterror("Floor RGB Error"));
	return (0);
}

int	init(t_core *core, char **argv)
{
	core->map = ft_calloc(1, sizeof(t_map));
	core->img = ft_calloc(1, sizeof(t_texture));
	core->img->celling = ft_calloc(1, sizeof(t_rgb));
	core->img->floor = ft_calloc(1, sizeof(t_rgb));
	init_path_null(core);
	if (open_file(core, argv))
		return (ft_puterror("The file can't be open"));
	if (parsing_data(core))
		return (ft_puterror("Parsing file data error"));
	if (data_error(core))
		return (1);
	if (parsing_map(core))
		return (ft_puterror("Parsing file map error"));
	return (0);
}
