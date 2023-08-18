/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-s <jlucas-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 21:22:23 by jlucas-s          #+#    #+#             */
/*   Updated: 2023/08/17 21:57:11 by jlucas-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	is_scapable(t_cub *cub, int x, int y)
{
	if (x == 0 || y == 0 || \
		x == cub->map->height - 1 || 
		y == (int)ft_strlen(cub->map->map[x]) - 1 || \
		y >= (int)ft_strlen(cub->map->map[x + 1]) || \
		y >= (int)ft_strlen(cub->map->map[x - 1]) || \
		!ft_strchr("01NESW", cub->map->map[x + 1][y]) || \
		!ft_strchr("01NESW", cub->map->map[x - 1][y]) || \
		!ft_strchr("01NESW", cub->map->map[x][y + 1]) || \
		!ft_strchr("01NESW", cub->map->map[x][y - 1]))
	{
		ft_putstr_fd("Error\ninvalid map\n", STDERR_FILENO);
		free_map(cub, 101);
	}
}

static void	player_validation(t_cub *cub, int x, int y)
{
	if (cub->map->map[x][y] != '0')
	{
		if (cub->map->player_x != 0 && cub->map->player_y != 0)
		{
			ft_putstr_fd("Error\nMore than one player on map\n", \
			STDERR_FILENO);
			free_map(cub, 111);
		}
		cub->map->player_x = x;
		cub->map->player_y = y;
	}
}

void	map_validation(t_cub *cub)
{
	int	x;
	int	y;

	cub->map->player_x = 0;
	cub->map->player_y = 0;
	x = 0;
	while (cub->map->map[x])
	{
		y = 0;
		while (cub->map->map[x][y])
		{
			if (ft_strchr("0NESW", cub->map->map[x][y]))
			{
				player_validation(cub, x, y);
				is_scapable(cub, x, y);
			}
			y++;
		}
		x++;
	}
	if (cub->map->player_x == 0 && cub->map->player_y == 0)
	{
		ft_putstr_fd("Error\nNo player on the map\n", STDERR_FILENO);
		free_map(cub, 112);
	}
}
