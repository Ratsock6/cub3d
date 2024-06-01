/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closed_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 18:27:27 by maxborde          #+#    #+#             */
/*   Updated: 2024/06/01 20:21:23 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	print_str_tab(char **str_tab)
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

void	fill_with_spaces(char *line, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		line[i] = ' ';
		i++;
	}
	line[i] = 0;
}

/*
If a cell is on the left extremity or the top extremity, or (i == 0, j == 0)),
it can't be a 0
//For cells that are not on the above extremities, we just check if the cell is
a 0, and it it is, we check
the 4 cells surrouding it. It can't be a NULL character, if it is, it means the
map is not closed.
*/
bool	check_cell(char **map, int i, int j)
{
	if (i == 0)
		if (map[i][j] == '0')
			return (false);
	if (j == 0)
		if (map[i][j] == '0')
			return (false);
	printf("YY\n");
	if (map[i + 1] && (map[i + 1][j] == '0' || map[i + 1][j] == '1')
		&& map[i - 1] && (map[i - 1][j] == '0' || map[i - 1][j] == '1')
		&& map[i][j + 1] && (map[i][j + 1] == '0' || map[i][j + 1] == '1')
		&& map[i][j - 1] && (map[i][j - 1] == '0' || map[i][j - 1] == '1'))
		return (true);
	else
		return (false);
}

bool	is_map_closed(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '0')
			{
				if (!check_cell(map, i, j))
					return (false);
			}
			j++;
		}
		i++;
	}
	return (true);
}
