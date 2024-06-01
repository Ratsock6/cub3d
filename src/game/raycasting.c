/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:55:44 by aallou-v          #+#    #+#             */
/*   Updated: 2024/06/01 20:43:42 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"


void	draw_column(int x, t_core *core)
{
	int			line_height;
	int			draw_end;
	int			draw_start;
	uint32_t	*texture_map;
	int			tex_x;
	int			tex_y;
	int			dist_to_top;
	int			y;
	uint32_t	color;

	line_height = (int)(core->map->screen_height / core->raycast.dist);
	draw_start = -line_height / 2 + core->map->screen_height / 2;
	draw_end = line_height / 2 + core->map->screen_height / 2;
	if (draw_start < 0)
		draw_start = 0;
	if (draw_end >= core->map->screen_height)
		draw_end = core->map->screen_height - 1;
	tex_x = (int)(core->raycast.wall_x * (double)core->img->text_width);
	tex_x = core->img->text_width - tex_x - 1;
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= core->img->text_width)
		tex_x = core->img->text_width - 1;
	if (core->raycast.side == 0)
	{
		if (core->raycast.ray_dir_x > 0)
			texture_map = core->img->text_map_east;
		else
			texture_map = core->img->text_map_west;
	}
	else
	{
		if (core->raycast.ray_dir_y > 0)
			texture_map = core->img->text_map_south;
		else
			texture_map = core->img->text_map_north;
	}
	y = draw_start;
	while (y < draw_end)
	{
		dist_to_top = y * 256 - core->map->screen_height * 128 + line_height
			* 128;
		tex_y = ((dist_to_top * core->img->text_width) / line_height) / 256;
		color = texture_map[core->img->text_width * tex_y + tex_x];
		mlx_put_pixel(core->raycast.image, x, y, color);
		y++;
	}
}

void	render(t_core *core)
{
	int		x;
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;

	mlx_delete_image(core->mlx, core->raycast.image);
	core->raycast.image = mlx_new_image(core->mlx, core->map->screen_width,
			core->map->screen_height);
	mlx_fill_image(core->raycast.image, core->img->celling->r,
		core->img->celling->g, core->img->celling->b);
	mlx_fill_floor(core->raycast.image, core->img->floor->r,
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
