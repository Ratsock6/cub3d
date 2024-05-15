/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:09:46 by aallou-v          #+#    #+#             */
/*   Updated: 2024/05/15 17:41:17 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_error(int argc, char **argv)
{
	if (argc != 2)
		return (ft_puterror("./cub3d <map>"));
	if (ft_strchr(argv[1], '.') == NULL
		|| ft_strcmp(ft_strchr(argv[1], '.'), ".cub") != 0)
		return (ft_puterror("The file is not a .cub"));
	return (0);
}
