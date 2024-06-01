/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_to_hex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 20:15:16 by aallou-v          #+#    #+#             */
/*   Updated: 2024/06/01 20:18:07 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	convert_to_hex(uint32_t *texture_map, uint8_t *pixels, int w, int h)
{
	int	i;
	int	r;
	int	g;
	int	b;
	int	a;

	i = 0;
	while (i < w * h)
	{
		r = pixels[i * 4];
		g = pixels[i * 4 + 1];
		b = pixels[i * 4 + 2];
		a = pixels[i * 4 + 3];
		texture_map[i] = ft_pixel(r, g, b, a);
		i++;
	}
}
