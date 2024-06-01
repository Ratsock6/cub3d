/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 18:24:39 by aallou-v          #+#    #+#             */
/*   Updated: 2024/05/21 16:55:57 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	pre_free_path(t_core *core)
{
	free(core->img->path_east);
	free(core->img->path_west);
	free(core->img->path_north);
	free(core->img->path_south);
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
	if ((core->img->celling->r > 255 || core->img->celling->r < 0)
		|| (core->img->celling->g > 255 || core->img->celling->g < 0)
		|| (core->img->celling->b > 255 || core->img->celling->b < 0)
	)
		return (ft_puterror("Celling RGB Error"));
	return (0);
}

static int	init_var(t_core *core)
{
	core->map = ft_calloc(1, sizeof(t_map));
	core->player = ft_calloc(1, sizeof(t_player));
	core->img = ft_calloc(1, sizeof(t_img));
	core->img->celling = ft_calloc(1, sizeof(t_rgb));
	core->img->floor = ft_calloc(1, sizeof(t_rgb));
	core->mlx = NULL;
	core->img->path_east = NULL;
	core->img->path_north = NULL;
	core->img->path_south = NULL;
	core->img->path_west = NULL;
	core->map->screen_height = SIZE_HEIGHT;
	core->map->screen_width = SIZE_WIDTH;
	core->pos[X] = -1;
	core->pos[Y] = -1;
	if (core->map == NULL || core->img == NULL || core->img->celling == NULL
		|| core->img->floor == NULL)
		return (ft_puterror("Malloc error"));
	return (0);
}

int	init(t_core *core, char **argv)
{
	if (init_var(core))
		return (ft_puterror("Error init var"));
	if (open_file(core, argv))
		return (ft_puterror("The file can't be open"));
	if (parsing_data(core))
	{
		pre_free_path(core);
		return (ft_puterror("Parsing file data error"));
	}
	if (data_error(core))
	{
		pre_free_path(core);
		return (ft_puterror("Data file error"));
	}
	if (init_texture(core))
		return (ft_puterror("Init Texture Error"));
	if (parsing_map(core))
		return (ft_puterror("Parsing file map error"));
	if (!is_map_closed(core->map->map))
		return (ft_puterror("Map is not closed"));
	return (0);
}
