/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-s <jlucas-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 21:42:21 by jlucas-s          #+#    #+#             */
/*   Updated: 2023/07/27 19:10:54 by jlucas-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void init_mlx(t_cub *cub)
{
    cub->mlx = malloc(sizeof(t_mlx));
    cub->mlx->mlx = mlx_init();
    if (cub->mlx->mlx == NULL)
        exit_cub(cub, 51);
    cub->mlx->win = mlx_new_window(cub->mlx->mlx, 800, 600, "CUB3D");
    if (cub->mlx->win == NULL)
        exit_cub(cub, 81);
    cub->mlx->img = mlx_new_image(cub->mlx->mlx, WIN_WIDTH, WIN_HEIGHT);
    cub->mlx->addr = mlx_get_data_addr(cub->mlx->img, &cub->mlx->bits_per_pixel, &cub->mlx->line_length, &cub->mlx->endian);
}
