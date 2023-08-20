/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-s <jlucas-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 21:42:21 by jlucas-s          #+#    #+#             */
/*   Updated: 2023/08/15 21:57:55 by jlucas-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_mlx(t_cub *cub)
{
	cub->mlx = malloc(sizeof(t_mlx));
	cub->mlx->mlx = mlx_init();
	if (cub->mlx->mlx == NULL)
	{
		free_map(cub, 0);
		free(cub->mlx);
		free(cub);
		exit(81);
	}
	cub->mlx->win = mlx_new_window(cub->mlx->mlx, \
	WIN_WIDTH, WIN_HEIGHT, "CUB3D");
	if (cub->mlx->win == NULL)
	{
		free_map(cub, 0);
		free_mlx(cub);
		free(cub);
		exit(82);
	}
}
