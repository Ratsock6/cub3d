/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_raycasting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 20:43:33 by aallou-v          #+#    #+#             */
/*   Updated: 2024/06/01 21:17:16 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
Initialisation des variables
- map_x et map_y :
Les coordonnées initiales du joueur sur la carte
converties en entiers pour référencer les cases de la carte

- delta_dist_x et delta_dist_x :
La distance que le rayon doit parcourir pour
traverser une unité de grille en x ou en y

- side_dist_x et side_dist_y
Les distances à parcourir pour atteindre la prochaine ligne de grille en x ou y
(Forcement init dans calcul_dist)

- step_x et step_y
La direction du déplacement sur la grille. (Forcement init dans calcul_dist)

- hit
Permet de faire la Boucle DDA
*/
static void	init_raycast(t_norm_fill *norm, t_core *core, \
	double ray_x, double ray_y)
{
	norm->hit = 0;
	norm->map_x = (int)core->player->pos_x;
	norm->map_y = (int)core->player->pos_y;
	norm->delta_dist_x = fabs(1 / ray_x);
	norm->delta_dist_y = fabs(1 / ray_y);
	core->raycast.ray_dir_x = ray_x;
	core->raycast.ray_dir_y = ray_y;
	norm->step_y = 1;
	norm->step_x = 1;
	norm->side_dist_x = 0;
	norm->side_dist_y = 0;
}

/*
Si le rayon se déplace vers la gauche (ray_dir_x < 0), step_x
est -1 et side_dist_x est calculé en fonction de la distance actuelle
du joueur à la ligne de grille précédente.

Si le rayon se déplace vers la droite (ray_dir_x >= 0), step_x 
est 1 et side_dist_x est calculé en fonction de la
distance à la ligne de grille suivante.

La même logique est appliquée pour stepY et sideDistY.
*/
static void	calcul_dist(t_norm_fill *norm, t_core *core)
{
	if (core->raycast.ray_dir_x < 0)
	{
		norm->step_x = -1;
		norm->side_dist_x = \
			(core->player->pos_x - norm->map_x) * norm->delta_dist_x;
	}
	else
	{
		norm->step_x = 1;
		norm->side_dist_x = \
			(norm->map_x + 1.0 - core->player->pos_x) * norm->delta_dist_x;
	}
	if (core->raycast.ray_dir_y < 0)
	{
		norm->step_y = -1;
		norm->side_dist_y = \
			(core->player->pos_y - norm->map_y) * norm->delta_dist_y;
	}
	else
	{
		norm->step_y = 1;
		norm->side_dist_y = \
			(norm->map_y + 1.0 - core->player->pos_y) * norm->delta_dist_y;
	}
}

/*
Boucle DDA (Digital Differential Analysis)
La boucle DDA continue jusqu'à ce que le rayon touche un mur (hit == 1).
side_dist_x et side_dist_y sont incrémentés jusqu'à atteindre la prochaine
ligne de grille.

map_x et map_y sont mis à jour en fonction de step_x et step_y respectivement.
side indique si l'impact s'est produit sur un mur vertical (side = 0) ou
horizontal (side = 1).
*/
static void	boucle_dda(t_norm_fill *norm, t_core *core)
{
	while (!norm->hit)
	{
		if (norm->side_dist_x < norm->side_dist_y)
		{
			norm->side_dist_x += norm->delta_dist_x;
			norm->map_x += norm->step_x;
			norm->side = 0;
		}
		else
		{
			norm->side_dist_y += norm->delta_dist_y;
			norm->map_y += norm->step_y;
			norm->side = 1;
		}
		if (core->map->map[norm->map_y][norm->map_x] == '1')
			norm->hit = 1;
	}
}

void	fill_raycast(double ray_dir_x, double ray_dir_y, t_core *core)
{
	t_norm_fill	norm;

	init_raycast(&norm, core, ray_dir_x, ray_dir_y);
	calcul_dist(&norm, core);
	boucle_dda(&norm, core);
	if (norm.side == 0)
		norm.perp_wall_dist = (norm.map_x - core->player->pos_x
				+ (1 - norm.step_x) / 2) / ray_dir_x;
	else
		norm.perp_wall_dist = (norm.map_y - core->player->pos_y
				+ (1 - norm.step_y) / 2) / ray_dir_y;
	if (norm.side == 0)
		norm.wall_x = core->player->pos_y + norm.perp_wall_dist * ray_dir_y;
	else
		norm.wall_x = core->player->pos_x + norm.perp_wall_dist * ray_dir_x;
	norm.wall_x -= floor(norm.wall_x);
	core->raycast.x = norm.map_x;
	core->raycast.y = norm.map_y;
	core->raycast.dist = norm.perp_wall_dist;
	core->raycast.side = norm.side;
	core->raycast.wall_x = norm.wall_x;
}
