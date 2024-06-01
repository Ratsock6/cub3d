/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:24:47 by aallou-v          #+#    #+#             */
/*   Updated: 2024/06/01 22:32:25 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	pre_add_line(char *line, int count, t_core *core)
{
	if (!ft_isonly(line, " \n10NSEW"))
		return (ft_puterror("A line in the map is invalid. ( 10NSEW\\n)"));
	if (count == 0)
		core->map->map = NULL;
	return (0);
}

static int	add_line_to_map(char *line, t_core *core)
{
	char		**tmp_map;
	static int	count = 0;
	int			i;

	if (pre_add_line(line, count, core))
		return (1);
	if (line[ft_strlen(line) - 1] == '\n')
		line[ft_strlen(line) - 1] = '\0';
	tmp_map = ft_calloc(count + 2, sizeof(char *));
	if (tmp_map == NULL)
		return (ft_puterror("Malloc Error (2)"));
	i = 0;
	if (core->map->map != NULL)
	{
		while (i < count)
		{
			tmp_map[i] = ft_strdup(core->map->map[i]);
			i++;
		}
		free_str_tab(core->map->map);
	}
	tmp_map[count] = line;
	tmp_map[count++ + 1] = 0;
	core->map->map = tmp_map;
	return (0);
}

void	init_plane(t_core *core, double plane_x, double plane_y \
	, double dir_x, double dir_y)
{
	core->player->dir_y = dir_y;
	core->player->dir_x = dir_x;
	core->player->plane_x = plane_x;
	core->player->plane_y = plane_y;
}

static int	where_is_player(char *line, t_core *core, int y, int x)
{
	x = -1;
	while (line[++x])
	{
		if (line[x] != 'N' && line[x] != 'S' && line[x] != 'E'
			&& line[x] != 'W')
			continue ;
		if (core->pos[Y] != -1)
			return (ft_puterror("Double player found"));
		core->player->pos_y = y + 0.5;
		core->player->pos_x = x + 0.5;
		core->player->dir_y = 0;
		core->pos[Y] = 1;
		if (core->map->map[y][x] == 'N')
			init_plane(core, 0.66, 0, 0, -1);
		if (core->map->map[y][x] == 'S')
			init_plane(core, -0.66, 0, 0, 1);
		if (core->map->map[y][x] == 'E')
			init_plane(core, 0, 0.66, 1, 0);
		if (core->map->map[y][x] == 'W')
			init_plane(core, 0, -0.66, -1, 0);
		core->map->map[y][x] = '0';
	}
	return (0);
}

int	parsing_map(t_core *core)
{
	char	*line;
	int		y;

	y = 0;
	while (1)
	{
		line = get_next_line(core->map->fd);
		if (line == NULL)
			break ;
		if (ft_isonly(line, "\n"))
		{
			free(line);
			continue ;
		}
		if (add_line_to_map(line, core))
			return (1);
		if (where_is_player(line, core, y, 0))
			return (1);
		core->map->height = y;
		if (ft_strlen(core->map->map[y]) >= core->map->width)
			core->map->width = ft_strlen(core->map->map[y]);
		y++;
	}
	return (0);
}
