/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:55:44 by aallou-v          #+#    #+#             */
/*   Updated: 2024/06/01 15:51:27 by aallou-v         ###   ########.fr       */
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

	double wallX;
	// printf("PLAYER Y = %lf\n", core->player->pos_y);
	// printf("PLAYER X = %lf\n", core->player->pos_x);
	if (side == 0) {
		wallX = core->player->pos_y + perp_wall_dist * rayDirY;
	} else {
		wallX = core->player->pos_x + perp_wall_dist * rayDirX;
	}
	wallX -= floor(wallX);
	core->raycast.x = map_x;
	core->raycast.y = map_y;
	core->raycast.dist = perp_wall_dist;
	core->raycast.side = side;
	core->raycast.wallX = wallX;
	//printf("WALL X = %lf\n", wallX);
}

void draw_column(int x, t_core *core) {
	printf("TEXT WIDTH = %d\n", core->img->text_width);
	int line_height; 
	int draw_end;
	int draw_start;
	uint32_t* texture_map;
	int	texX;

	line_height = (int)(core->map->screen_height / core->raycast.dist); //La taille du wall, grace a raycast.dist et la taille de l'ecra
	draw_start = -line_height / 2 + core->map->screen_height / 2; //Le point de depart pour dessiner le wall (sur l'axe y)
	draw_end = line_height / 2 + core->map->screen_height / 2; // Le point de fin pour le wall (sur l'axe y)
	//Les lignes en dessous servent a  s'assurer que draw_start et draw_end ne soit pas soit negatif soit plus grand que la taille de l'ecran car on ne peut pas commencer dessiner a -300 ou a plus que la taille de l'ecran.  On arrive souvent a des valeurs de ce genre si on se colle au mur.
	if (draw_start < 0) 
		draw_start = 0;
	if (draw_end >= core->map->screen_height) 
		draw_end = core->map->screen_height - 1;


	//Les lignes en dessous vont nous permettre de calculer les coordonnes de la texture sur l'axe X.
	//Imaginons un carre de 32x32 representant notre texture. On a wallX qui est une valeur de 0 a 1 representant
	//l'endroit ou le ray a touche une case sur l'axe X (0 si il a hit l'extreme gauche de la case, 0.5 au milieu, 1
	//si c'est l'extreme droite ect. On va donc prendre wallX et le multiplier par la largeur de notre texture (ici 32)
	//pour trouver le pixel sur l'axe X que l'on veut afficher.
	texX = (int)(core->raycast.wallX * (double)core->img->text_width);
	texX =core->img->text_width - texX - 1;
	// On s'assure que texX reste entre 0 et 31 pour ne pas aller chercher un pixel qui n'existe pas
	if (texX < 0) 
		texX = 0;
	if (texX >=core->img->text_width) 
		texX =core->img->text_width - 1;

	//Ici, on utilise side (side == 0 veut dire qu'on a touche un mur verticalement alors que side == 1 veut dire qu'on a touche un mur horizontal) et raycast.x et raycast.y qu'on a calcule dans le raycast pour choisir quelle texture_map choisir avant de recuperer les pixel.
	//raycast.x et raycast.y sont les coordonnes  de l'endroit ou le rayon a hit le wall, sur leur axes respectifs.
	//Par exemple, si le joueur regarde tout droit vers le nord, raycast.x est a 0 et raycast.y est a -1 (et sera 1 si on regarde tout 
	//droit vers le sud)
	//Grace a cette logique on peut determiner laquelle des 4 textures on doit choisir pour dessiner notre bout de mur.
	if (core->raycast.side == 0) {
		if (core->raycast.x > 0)
			texture_map = core->img->text_map_east;
		else
			texture_map = core->img->text_map_west;
	} else {
		if (core->raycast.y > 0)
			texture_map = core->img->text_map_south;
		else
			texture_map = core->img->text_map_north;
	}

	//Grace a tout ces calculs, on peut enfin dessiner la colonne. 
	//On utilise bien sur draw_start et draw_end pour la taille de la colonne.
	//Pour choisir le pixel sur l'axe Y de la texture_map on va calculer texY, et on va s'aider de distToTop qui est distance du haut de l'ecran jusqu'au pixel actuel qui va etre dessine. cette variable est multiplie par 256 pour la precision, mais sera redivise par 256 quand on calculera texY.
	for (int y = draw_start; y < draw_end; y++) {
		int distToTop = y * 256 - core->map->screen_height * 128 + line_height * 128;
		int texY = ((distToTop * core->img->text_width) / line_height) / 256;
		uint32_t color = texture_map[core->img->text_width * texY + texX];
		//Grace a ces calculs, on peut enfin pick le pixel dans la texture_map. Si side == 1, donc que le mur est vertical, on l'assombrit un petit peu.
		if (core->raycast.side == 1) 
			color = (color >> 1) & 8355711;
		mlx_put_pixel(core->raycast.image, x, y, color);
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
