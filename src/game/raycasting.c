/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:55:44 by aallou-v          #+#    #+#             */
/*   Updated: 2024/05/30 18:50:29 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	fill_raycast(double rayDirX, double rayDirY, t_core *core)
{
	int			mapX;
	int			mapY;
	double		sideDistX;
	double		sideDistY;
	double		deltaDistX;
	double		deltaDistY;
	double		perpWallDist;
	int			stepX;
	int			stepY;
	int			hit;
	int			side;

	hit = 0;
	mapX = (int) core->player->pos_x;
	mapY = (int) core->player->pos_y;
	deltaDistX = fabs(1 / rayDirX);
	deltaDistY = fabs(1 / rayDirY);
	if (rayDirX < 0)
	{
		stepX = -1;
		sideDistX = (core->player->pos_x - mapX) * deltaDistX;
	} 
	else
	{
		stepX = 1;
		sideDistX = (mapX + 1.0 - core->player->pos_x) * deltaDistX;
	}
	if (rayDirY < 0)
	{
		stepY = -1;
		sideDistY = (core->player->pos_y - mapY) * deltaDistY;
	}
	else
	{
		stepY = 1;
		sideDistY = (mapY + 1.0 - core->player->pos_y) * deltaDistY;
	}
	while (!hit)
	{
		if (sideDistX < sideDistY)
		{
			sideDistX += deltaDistX;
			mapX += stepX;
			side = 0;
		}
		else
		{
			sideDistY += deltaDistY;
			mapY += stepY;
			side = 1;
		}
		if (core->map->map[mapY][mapX] == '1')
			hit = 1;
	}
	if (side == 0)
		perpWallDist = (mapX - core->player->pos_x + (1 - stepX) / 2) / rayDirX;
	else
		perpWallDist = (mapY - core->player->pos_y + (1 - stepY) / 2) / rayDirY;
	core->raycast.x = mapX;
	core->raycast.y = mapY;
	core->raycast.dist = perpWallDist;
	core->raycast.side = side;
}

void	draw_column(int x, t_core *core)
{
	int			line_height;
	int			draw_start;
	int			draw_end;
	uint32_t	color;
	int			y;

	line_height = (int)(core->map->screen_height / core->raycast.dist);
	draw_start = -line_height / 2 + core->map->screen_height / 2;
	draw_end = line_height / 2 + core->map->screen_height / 2;
	if (draw_start < 0)
		draw_start = 0;
	if (draw_end >= core->map->screen_height)
		draw_end = core->map->screen_height - 1;
	if (core->raycast.side == 1)
		color = 0xAAAAAAFF;
	else
		color = 0xFFFFFFFF;
	y = draw_start;
	while (y < draw_end)
	{
		mlx_put_pixel(core->raycast.image, x, y, color);
		y++;
	}
}

void	render(t_core *core)
{
	int			x;
	double		cameraX;
	double		rayDirX;
	double		rayDirY;

	mlx_delete_image(core->mlx, core->raycast.image);
	core->raycast.image = mlx_new_image(core->mlx, core->map->screen_width, core->map->screen_height);
	mlx_fill_image(core->raycast.image, 0, 0, 0);
	x = 0;
	while (x < core->map->screen_width)
	{
		cameraX = 2 * x / (double)core->map->screen_width - 1;
		rayDirX = core->player->dirX + core->player->planeX * cameraX;
		rayDirY = core->player->dirY + core->player->planeY * cameraX;
		fill_raycast(rayDirX, rayDirY, core);
		draw_column(x, core);
		x++;
	}
	mlx_image_to_window(core->mlx, core->raycast.image, 0, 0);
}
