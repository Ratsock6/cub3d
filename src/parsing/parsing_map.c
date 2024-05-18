/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:24:47 by aallou-v          #+#    #+#             */
/*   Updated: 2024/05/15 18:30:23 by maxborde         ###   ########.fr       */
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

static int	where_is_player(char *line, t_core *core, int y)
{
	int	x;

	x = -1;
	while (line[++x])
	{
		if (line[x] != 'N' && line[x] != 'S' && line[x] != 'E'
			&& line[x] != 'W')
			continue ;
		if (core->pos[y] != -1)
			return (ft_puterror("Double player found"));
		core->pos[Y] = y;
		core->pos[X] = x;
		if (line[x] == 'N')
			core->direction = NORTH;
		if (line[x] == 'S')
			core->direction = SOUTH;
		if (line[x] == 'E')
			core->direction = EAST;
		if (line[x] == 'W')
			core->direction = WEST;
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
		if (where_is_player(line, core, y))
			return (1);
		y++;
	}
	return (0);
}