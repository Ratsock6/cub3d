/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxborde <maxborde@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 13:51:53 by maxborde          #+#    #+#             */
/*   Updated: 2024/05/17 16:32:43 by maxborde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	width = 1920;
int	height = 1080;

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}


void	mlx_draw_verline(t_core *core, int x, int drawStart, int drawEnd)
{
	int	y;

	y = 0;
	while (y < height)
	{
		if (y >= drawStart && y <= drawEnd)
			mlx_put_pixel(core->image, x, y, 165530195); 
		else
			mlx_put_pixel(core->image, x, y, 295530195); 
		y++;
	}
}

// void	rendering_test(t_core *core)
// {
// 	core->image = mlx_new_image(core->mlx, width, height);
// 	mlx_image_to_window(core->mlx, core->image, 0, 0);
// 	mlx_put_pixel(core->image, 0, 500, color); 
// 	mlx_put_pixel(core->image, 0, 501, color); 
// 	mlx_put_pixel(core->image, 0, 502, color); 
// 	mlx_put_pixel(core->image, 0, 503, color); 
// 	mlx_put_pixel(core->image, 0, 504, color); 
// 	mlx_loop(core->mlx);
// 	printf("DONE\n");
// }
//
void	draw_player(char **map, mlx_image_t *image)
{
	int	x;
	int	y;

	y = 0;
	while(map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'S')
				mlx_put_pixel(image, (64 * x) + 32, (64 * y) + 32, 200000); 
			x++;
		}
		y++;
	}
}

void	draw_tile(int x, int y, mlx_image_t *image, char tile_type)
{
	int	i;
	int	j;

	i = 0;
	while(i < 64)
	{
		j = 0;
		while (j < 64)
		{
			if (tile_type == '1')
				mlx_put_pixel(image, (64 * x) + i, (64 * y) + j, 400000); 
			if (tile_type == '0' || tile_type == 'S')
				mlx_put_pixel(image, (64 * x) + i, (64 * y) + j, 600000); 
			j++;
		}
		i++;
	}
}

void	draw_map(char **map, mlx_image_t *image)
{
	int	x;
	int	y;

	y = 0;
	while(map[y])
	{
		x = 0;
		while (map[y][x])
		{
			draw_tile(x, y, image, map[y][x]);
			x++;
		}
		y++;
	}
}

void	rendering(t_core *core)
{
	core->image = mlx_new_image(core->mlx, width, height);
	mlx_image_to_window(core->mlx, core->image, 0, 0);
	draw_map(core->map->map, core->image);
	draw_player(core->map->map, core->image);
	mlx_loop(core->mlx);
}
