/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:55:44 by aallou-v          #+#    #+#             */
/*   Updated: 2024/05/31 15:43:43 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	fill_raycast(double rayDirX, double rayDirY, t_core *core)
{
	int			map_x;
	int			map_y;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		perp_wall_dist;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;

	hit = 0;
	map_x = (int) core->player->pos_x;
	map_y = (int) core->player->pos_y;
	delta_dist_x = fabs(1 / rayDirX);
	delta_dist_y = fabs(1 / rayDirY);
	if (rayDirX < 0)
	{
		step_x = -1;
		side_dist_x = (core->player->pos_x - map_x) * delta_dist_x;
	}
	else
	{
		step_x = 1;
		side_dist_x = (map_x + 1.0 - core->player->pos_x) * delta_dist_x;
	}
	if (rayDirY < 0)
	{
		step_y = -1;
		side_dist_y = (core->player->pos_y - map_y) * delta_dist_y;
	}
	else
	{
		step_y = 1;
		side_dist_y = (map_y + 1.0 - core->player->pos_y) * delta_dist_y;
	}
	while (!hit)
	{
		if (side_dist_x < side_dist_y)
		{
			side_dist_x += delta_dist_x;
			map_x += step_x;
			side = 0;
		}
		else
		{
			side_dist_y += delta_dist_y;
			map_y += step_y;
			side = 1;
		}
		if (core->map->map[map_y][map_x] == '1')
			hit = 1;
	}
	if (side == 0)
		perp_wall_dist = (map_x - core->player->pos_x + (1 - step_x) / 2) / rayDirX;
	else
		perp_wall_dist = (map_y - core->player->pos_y + (1 - step_y) / 2) / rayDirY;
	core->raycast.x = map_x;
	core->raycast.y = map_y;
	core->raycast.dist = perp_wall_dist;
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
	double		camera_x;
	double		ray_dir_x;
	double		ray_dir_y;

	mlx_delete_image(core->mlx, core->raycast.image);
	core->raycast.image = mlx_new_image(core->mlx, core->map->screen_width, \
		core->map->screen_height);
	mlx_fill_image(core->raycast.image, core->img->celling->r, \
		core->img->celling->g, core->img->celling->b);
	mlx_fill_floor(core->raycast.image, core->img->floor->r, \
		core->img->floor->g, core->img->floor->b);
	x = 0;
	while (x < core->map->screen_width)
	{
		camera_x = 2 * x / (double)core->map->screen_width - 1;
		ray_dir_x = core->player->dir_x + core->player->plane_x * camera_x;
		ray_dir_y = core->player->dir_y + core->player->plane_y * camera_x;
		fill_raycast(ray_dir_x, ray_dir_y, core);
		draw_column(x, core);
		x++;
	}
	mlx_image_to_window(core->mlx, core->raycast.image, 0, 0);
}
