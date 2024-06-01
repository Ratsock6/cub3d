/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 20:22:48 by aallou-v          #+#    #+#             */
/*   Updated: 2024/06/01 20:23:07 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	rgb(t_rgb *rgb, char **values)
{
	rgb->r = ft_atoi(values[0]);
	rgb->g = ft_atoi(values[1]);
	rgb->b = ft_atoi(values[2]);
}
