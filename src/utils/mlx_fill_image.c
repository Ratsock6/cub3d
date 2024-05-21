/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_fill_image.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 16:05:19 by aallou-v          #+#    #+#             */
/*   Updated: 2024/05/21 16:16:00 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	mlx_fill_image(mlx_image_t *img, int32_t r, int32_t g, int32_t b)
{
	unsigned int	i;
	unsigned int	x;

	i = 0;
	while (i <= img->height - 1)
	{
		x = 0;
		while (x <= img->width - 1)
		{
			mlx_put_pixel(img, i, x, ft_pixel(r, g, b, 255));
			x++;
		}
		i++;
	}
}
