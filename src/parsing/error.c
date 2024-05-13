/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:09:46 by aallou-v          #+#    #+#             */
/*   Updated: 2024/05/13 18:50:53 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_puterror(char *error)
{
	ft_putendl_fd("\033[38;2;247;59;25;1mERROR", 2);
	ft_putstr_fd(error, 2);
	ft_putendl_fd("\033[0m", 2);
	return (1);
}

static int	open_file(t_core *core, char **argv)
{
	core->map->fd = open(argv[1], O_RDONLY);
	if (core->map->fd <= 0)
		return (1);
	return (0);
}

int	check_error(int argc, char **argv, t_core *core)
{
	if (argc != 2)
		return (ft_puterror("./cub3d <map>"));
	if (ft_strchr(argv[1], '.') == NULL
		|| ft_strcmp(ft_strchr(argv[1], '.'), ".cub") != 0)
		return (ft_puterror("The file is not a .cub"));
	if (open_file(core, argv))
		return (ft_puterror("The file can't be open"));
	return (0);
}