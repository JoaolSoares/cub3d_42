/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-s <jlucas-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 21:22:23 by jlucas-s          #+#    #+#             */
/*   Updated: 2023/06/28 22:00:12 by jlucas-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	is_scapable(t_cub *cub, int x, int y)
{
	if (x == 0 || y == 0 ||									\
		x == cub->map->height - 1 ||						\
		y == (int)ft_strlen(cub->map->map[x]) - 1 ||		\
		y >= (int)ft_strlen(cub->map->map[x + 1]) ||		\
		y >= (int)ft_strlen(cub->map->map[x - 1]) ||		\
		!ft_strchr("01NESW", cub->map->map[x + 1][y]) ||	\
		!ft_strchr("01NESW", cub->map->map[x - 1][y]) ||	\
		!ft_strchr("01NESW", cub->map->map[x][y + 1]) ||	\
		!ft_strchr("01NESW", cub->map->map[x][y - 1]))

	{
		ft_putstr_fd("Error\ninvalid map\n", STDERR_FILENO);
		exit_cub(cub, 51);
	}
}

void map_validation(t_cub *cub)
{
    int x;
    int y;

    x = 0;
    while(cub->map->map[x])
    {
        y = 0;
        while(cub->map->map[x][y])
        {
            if(ft_strchr("0NESW", cub->map->map[x][y]))
            	is_scapable(cub, x, y);
            y++;
        }
        x++;
    }
}
