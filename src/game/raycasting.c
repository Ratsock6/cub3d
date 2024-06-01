/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:55:44 by aallou-v          #+#    #+#             */
/*   Updated: 2024/06/01 21:33:11 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
		draw_column(core, x);
		x++;
	}
	mlx_image_to_window(core->mlx, core->raycast.image, 0, 0);
}
