/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:30:12 by aallou-v          #+#    #+#             */
/*   Updated: 2024/06/02 16:09:28 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	free_put_value(char **split, char *tmp)
{
	free(tmp);
	free_str_tab(split);
}

static void	reform(char *str, bool new_line)
{
	int	len;
	int	i;
	int	j;

	if (str == NULL)
		return ;
	len = ft_strlen(str);
	if (new_line)
		str[len - 1] = '\0';
	i = -1;
	while (++i < len)
	{
		if (str[i] != ' ')
			break ;
	}
	if (i > 0)
	{
		j = -1;
		while (++j < len - i)
		{
			str[j] = str[j + i];
		}
		str[j] = '\0';
	}
}

static int	put_value_rgb(char *str, t_core *core)
{
	char	*tmp;
	char	**split;

	if (!((str[0] == 'F' && str[1] == ' ') || (str[0] == 'C' && str[1] == ' ')))
		return (0);
	tmp = ft_strdup(str + 2);
	reform(tmp, false);
	remove_spaces(tmp);
	if (ft_strlen(tmp) > 11)
	{
		free(tmp);
		return (ft_puterror("RGB values line too long"));
	}
	split = ft_split(tmp, ',');
	if (ft_len_tab(split) != 3)
	{
		free_put_value(split, tmp);
		return (ft_puterror("RGB values (2)"));
	}
	if (str[0] == 'F' && str[1] == ' ')
		rgb(core->img->floor, split);
	if (str[0] == 'C' && str[1] == ' ')
		rgb(core->img->celling, split);
	free_put_value(split, tmp);
	return (0);
}

static int	put_value(char *str, t_core *core)
{
	reform(str, true);
	if (ft_strlen(str) <= 3)
	{
		free(str);
		return (1);
	}
	if (str[0] == 'N' && str[1] == 'O' && str[2] == ' ')
		core->img->path_north = ft_strdup(str + 3);
	if (str[0] == 'S' && str[1] == 'O' && str[2] == ' ')
		core->img->path_south = ft_strdup(str + 3);
	if (str[0] == 'W' && str[1] == 'E' && str[2] == ' ')
		core->img->path_west = ft_strdup(str + 3);
	if (str[0] == 'E' && str[1] == 'A' && str[2] == ' ')
		core->img->path_east = ft_strdup(str + 3);
	reform(core->img->path_north, false);
	reform(core->img->path_south, false);
	reform(core->img->path_east, false);
	reform(core->img->path_west, false);
	if (put_value_rgb(str, core))
	{
		free(str);
		return (1);
	}
	free(str);
	return (0);
}

int	parsing_data(t_core *core)
{
	char	*line;
	int		i;

	i = 0;
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
		if (put_value(line, core))
			return (1);
		i++;
		if (i > 5)
			break ;
	}
	return (0);
}
