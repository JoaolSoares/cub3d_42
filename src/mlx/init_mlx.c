/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-s <jlucas-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 21:42:21 by jlucas-s          #+#    #+#             */
/*   Updated: 2023/07/04 21:42:35 by jlucas-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
