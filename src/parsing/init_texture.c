/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 11:24:43 by aallou-v          #+#    #+#             */
/*   Updated: 2024/05/17 13:56:50 by maxborde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static mlx_image_t	*load_image(mlx_t *mlx, char *path)
{
	mlx_texture_t	*texture;
	mlx_image_t		*result;

	texture = mlx_load_png(path);
	free(path);
	if (texture == NULL)
		return (NULL);
	result = mlx_texture_to_image(mlx, texture);
	mlx_delete_texture(texture);
	return (result);
}

int	init_texture(t_core *core)
{
	core->mlx = mlx_init(1920, 1080, "CUB3D", true);
	if (core->mlx == NULL)
		return (ft_puterror("Error MLX init"));
	core->img->img_north = load_image(core->mlx, core->img->path_north);
	core->img->img_south = load_image(core->mlx, core->img->path_south);
	core->img->img_east = load_image(core->mlx, core->img->path_east);
	core->img->img_west = load_image(core->mlx, core->img->path_west);
	if (core->img->img_north == NULL || core->img->img_south == NULL
		|| core->img->img_east == NULL || core->img->img_west == NULL)
		return (ft_puterror("Image not load"));
	return (0);
}
