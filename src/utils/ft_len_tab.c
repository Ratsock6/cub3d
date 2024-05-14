/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_len_tab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:59:47 by aallou-v          #+#    #+#             */
/*   Updated: 2024/05/14 17:01:10 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

size_t  ft_len_tab(char **str_tab)
{
    size_t	i;

    i = 0;
	if (str_tab)
	{
		while (str_tab[i])
			i++;
	}
    return (i);
}
