/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxborde <maxborde@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 18:27:27 by maxborde          #+#    #+#             */
/*   Updated: 2024/05/15 20:52:01 by maxborde         ###   ########.fr       */
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

bool	check_cell(char **map, int i, int j)
{
	if ((i == 0 && map[i][j] == ' ') || (j == 0 && map[i][j] == ' ') || 
		(j == ft_strlen(map[i]) && map[i][j] == ' '))// check for i == number of lines
		return (false);
	if ((!map[i + 1][j] && map[i + 1][j] != ' ') || 
		(!map[i - 1][j] && map[i - 1][j] != ' ') || 
		(!map[i][j + 1] && map[i][j + 1] != ' ') || 
		(!map[i][j - 1] && map[i][j - 1] != ' '))
		return  (false);
	return (true);
}

bool	is_map_closed(char **map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[i++])
	{
		while(map[j++])
		{
			if (map[i][j] == '0' || map[i][j] == 'S') //or other letters
				return (true);
		}
	}
	return (true);	
}
