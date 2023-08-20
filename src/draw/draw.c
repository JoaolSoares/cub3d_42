/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-s <jlucas-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 19:44:21 by jlucas-s          #+#    #+#             */
/*   Updated: 2023/08/16 21:50:41 by jlucas-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	pixel_put(t_cub *cub, int x, int y, int color)
{
	char	*dst;

	if (x < 0)
		x = 0;
	if (y < 0)
		y = 0;
	if (x > WIN_WIDTH)
		x = WIN_WIDTH;
	if (y > WIN_HEIGHT)
		y = WIN_HEIGHT;
	dst = cub->mlx->addr + \
	(y * cub->mlx->line_length + x * (cub->mlx->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

static void	floor_and_ceiling(t_cub *cub)
{
	int	x;
	int	y;

	x = 0;
	while (x++ < WIN_WIDTH)
	{
		y = 0;
		while (y++ < WIN_HEIGHT / 2)
			pixel_put(cub, x, y, cub->map->ceil_color);
	}
	x = 0;
	while (x++ < WIN_WIDTH)
	{
		y = WIN_HEIGHT / 2;
		while (y++ < WIN_HEIGHT)
			pixel_put(cub, x, y, cub->map->floor_color);
	}
}

void	draw(t_cub *cub)
{
	cub->mlx->img = mlx_new_image(cub->mlx->mlx, WIN_WIDTH, WIN_HEIGHT);
	cub->mlx->addr = mlx_get_data_addr(cub->mlx->img, \
	&cub->mlx->bits_per_pixel, &cub->mlx->line_length, &cub->mlx->endian);
	floor_and_ceiling(cub);
	raycasting(cub);
	mlx_put_image_to_window(cub->mlx->mlx, cub->mlx->win, cub->mlx->img, 0, 0);
	mlx_destroy_image(cub->mlx->mlx, cub->mlx->img);
}
