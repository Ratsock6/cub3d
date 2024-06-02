/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_space.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 15:50:40 by aallou-v          #+#    #+#             */
/*   Updated: 2024/06/02 15:58:02 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	remove_spaces(char *str)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != ' ')
			str[j++] = str[i];
		i++;
	}
	str[j] = '\0';
}
