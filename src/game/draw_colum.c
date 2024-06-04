/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_colum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 21:25:42 by aallou-v          #+#    #+#             */
/*   Updated: 2024/06/04 14:18:54 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
Initialisation des variables
- line_height
La hauteur de la colonne à dessiner
Elle est calculé avec la distance de raycast.dist du joueur au mur
plus la distance est petit, plus la colonne est haut

- drawStart et drawEnd
La ou va commencer la ligne, et se finir sur l'ecran
*/
static void	init_draw_column(t_norm_draw *norm, t_core *core)
{
	norm->line_height = (int)(core->map->screen_height / core->raycast.dist);
	norm->draw_start = -norm->line_height / 2 + core->map->screen_height / 2;
	norm->draw_end = norm->line_height / 2 + core->map->screen_height / 2;
	if (norm->draw_start < 0)
		norm->draw_start = 0;
	if (norm->draw_end >= core->map->screen_height)
		norm->draw_end = core->map->screen_height;
	norm->tex_x = (int)(core->raycast.wall_x * (double)core->img->text_width);
	norm->tex_x = core->img->text_width - norm->tex_x - 1;
	if (norm->tex_x < 0)
		norm->tex_x = 0;
	if (norm->tex_x >= core->img->text_width)
		norm->tex_x = core->img->text_width - 1;
}

/*
Permet de choisir la texture
Si side = 0 alors la texture choisi sera soit EAST ou WEST selon le ray_dir_x

Meme logique mais si le side = 1
*/
static void	choose_texture(t_core *core, t_norm_draw *norm)
{
	if (core->raycast.side == 0)
	{
		if (core->raycast.ray_dir_x > 0)
			norm->texture_map = core->img->text_map_west;
		else
			norm->texture_map = core->img->text_map_east;
	}
	else
	{
		if (core->raycast.ray_dir_y > 0)
			norm->texture_map = core->img->text_map_north;
		else
			norm->texture_map = core->img->text_map_south;
	}
}

void	draw_column(t_core *core, int x)
{
	t_norm_draw	norm;

	init_draw_column(&norm, core);
	choose_texture(core, &norm);
	norm.y = norm.draw_start;
	while (norm.y < norm.draw_end)
	{
		norm.dist_to_top = norm.y * 256 - core->map->screen_height
			* 128 + norm.line_height * 128;
		norm.tex_y = ((norm.dist_to_top * core->img->text_width)
				/ norm.line_height) / 256;
		norm.color = norm.texture_map[core->img->text_width
			* norm.tex_y + norm.tex_x];
		mlx_put_pixel(core->raycast.image, x, norm.y, norm.color);
		norm.y++;
	}
}
