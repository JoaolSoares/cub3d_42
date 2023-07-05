/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dofranci <dofranci@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 19:44:21 by jlucas-s          #+#    #+#             */
/*   Updated: 2023/07/04 21:16:59 by dofranci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	my_mlx_pixel_put(t_cub *cub, int x, int y, int color)
{
	char	*dst;

	dst = cub->mlx->addr + (y * cub->mlx->line_length + x * (cub->mlx->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int rgbToHex(int r, int g, int b) 
{
    int hexValue;

    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
    {
        printf("Valores RGB inválidos.\n");
        return (-1);
    }
    hexValue = (r << 16) | (g << 8) | b;
    return (hexValue);
}

int color_converter(char *rgb)
{
    int hex;
    char **str;

    str = ft_split(rgb, ',', 0);
    hex = rgbToHex(ft_atoi(str[0]), ft_atoi(str[1]), ft_atoi(str[2]));
    ft_freemtx(str);
    return(hex);
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
        my_mlx_pixel_put(cub, x, y, color_converter(cub->map->textures[C])); // converter cor
    }
    x = 0;
    while(x++ < 800)
    {
      y = 300;
      while(y++ < 600)
        my_mlx_pixel_put(cub, x, y, color_converter(cub->map->textures[F])); // converter cor
    }
}

int    x_hook(t_cub *cub)
{
    exit_cub(cub, 1);
    return (0);
}

void draw(t_cub *cub)
{
    floor_and_ceiling(cub);
    // walls(cub);
    mlx_put_image_to_window(cub->mlx->mlx, cub->mlx->win, cub->mlx->img, 0, 0);
    mlx_hook(cub->mlx->win, DestroyNotify, NoEventMask, x_hook, cub);
    mlx_loop(cub->mlx->mlx);
}

void init_mlx(t_cub *cub)
{
    cub->mlx = malloc(sizeof(t_mlx));
    cub->mlx->mlx = mlx_init();
    cub->mlx->win = mlx_new_window(cub->mlx->mlx, 800, 600, "CUB3D");
    cub->mlx->img = mlx_new_image(cub->mlx->mlx, 800, 600);
    if (cub->mlx->mlx == NULL || cub->mlx->win == NULL || cub->mlx->img == NULL)
      exit(120) ; //  dar free antes do exit
    cub->mlx->addr = mlx_get_data_addr(cub->mlx->img, &cub->mlx->bits_per_pixel, &cub->mlx->line_length, &cub->mlx->endian);
}
