/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-s <jlucas-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 19:44:21 by jlucas-s          #+#    #+#             */
/*   Updated: 2023/07/04 22:04:29 by jlucas-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	pixel_put(t_cub *cub, int x, int y, int color)
{
	char	*dst;

	dst = cub->mlx->addr + (y * cub->mlx->line_length + x * (cub->mlx->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

static void floor_and_ceiling(t_cub *cub)
{
    int x;
    int y;

    x = 0;
    while(x++ < 800)
    {
      y = 0;
      while(y++ < 300)
        pixel_put(cub, x, y, cub->map->ceil_color);
    }
    x = 0;
    while(x++ < 800)
    {
      y = 300;
      while(y++ < 600)
        pixel_put(cub, x, y, cub->map->floor_color);
    }
}

void draw(t_cub *cub)
{
    floor_and_ceiling(cub);
    // walls(cub);
    mlx_put_image_to_window(cub->mlx->mlx, cub->mlx->win, cub->mlx->img, 0, 0);

}
