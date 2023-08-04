/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-s <jlucas-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 21:57:56 by jlucas-s          #+#    #+#             */
/*   Updated: 2023/08/04 16:55:57 by jlucas-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	exit_cub(t_cub *cub, int i)
{
	if(i != 51)
	{
		mlx_destroy_window(cub->mlx->mlx, cub->mlx->win);
		mlx_destroy_display(cub->mlx->mlx);
		mlx_loop_end(cub->mlx->mlx);
		free(cub->mlx->mlx);
		free(cub->mlx);
	}
	ft_freemtx(cub->map->textures);
	ft_freemtx(cub->map->map);
	free(cub->player);
	free(cub->map);
	free(cub);

	exit(i);
}

void	init_player(t_cub *cub)
{ 
	cub->player = malloc(sizeof(t_player));
	// dependendo da letra do mapa vai mudar o angulo
	// cub->player->deltaPosA = PI;
	// cub->player->deltaPosX = cos(cub->player->deltaPosA) * 5;
	// cub->player->deltaPosY = sin(cub->player->deltaPosA) * 5;
	
	// Pos
	cub->player->posx = (double)cub->map->player_x;
	cub->player->posy = (double)cub->map->player_y;
	// cub->player->posx = 5;
	// cub->player->posy = 5;
	// dir
	cub->player->dirX = 0;
	cub->player->dirY = -1; 

	// Plane
	cub->player->planeX = 0.66; 
	cub->player->planeY = 0; 

	// cub->player->time = 0; 
	// cub->player->oldTime = 0; 
}