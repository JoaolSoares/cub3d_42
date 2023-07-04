/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-s <jlucas-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 19:44:21 by jlucas-s          #+#    #+#             */
/*   Updated: 2023/06/28 21:08:27 by jlucas-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	my_mlx_pixel_put(t_cub *cub, int x, int y, int color)
{
	char	*dst;

	dst = cub->addr + (y * cub->line_length + x * (cub->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

static void draw_floor_and_ceiling(t_cub *cub)
{
    int x;
    int y;

    x = 0;
    while(x++ < 800)
    {
      y = 0;
      while(y++ < 300)
        my_mlx_pixel_put(cub, x, y, 0x00FF0000); // converter cor
    }
    x = 0;
    while(x++ < 800)
    {
      y = 300;
      while(y++ < 600)
        my_mlx_pixel_put(cub, x, y, 0x0000FF); // converter cor
    }
}

static void start_mlx(t_cub *cub)
{
    int offset;

    cub->mlx = mlx_init();
    cub->win = mlx_new_window(cub->mlx, 800, 600, "CUB3D");
    cub->img = mlx_new_image(cub->mlx, 800, 600);
    if (cub->mlx == NULL || cub->win == NULL || cub->img == NULL)
      exit(120) ; //  dar free antes do exit
    cub->addr = mlx_get_data_addr(cub->img, &cub->bits_per_pixel, &cub->line_length, &cub->endian);
    offset = (cub->map->height * cub->line_length + cub->map->width * (cub->bits_per_pixel / 8));

}

void init_cub(t_cub *cub)
{
    start_mlx(cub);
    draw_floor_and_ceiling(cub);
    //desenhar_paredes();
    mlx_put_image_to_window(cub->mlx, cub->win, cub->img, 0, 0);
    mlx_loop(cub->mlx);
}
