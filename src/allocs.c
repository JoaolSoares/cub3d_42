/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-s <jlucas-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 21:57:56 by jlucas-s          #+#    #+#             */
/*   Updated: 2023/08/09 19:07:53 by jlucas-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void free_map(t_cub *cub)
{
	ft_freemtx(cub->map->textures);
	ft_freemtx(cub->map->map);
	free(cub->map);
}

void free_textures(t_cub *cub)
{
	int i;
	int j;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < cub->tx_data[i]->altura)
			free(cub->tx_data[i]->texture[j]);
		free(cub->tx_data[i]->texture);
	}
	i = -1;
	while(++i < 4)
		free(cub->tx_data[i]);
}

void free_mlx(t_cub *cub)
{
	mlx_destroy_window(cub->mlx->mlx, cub->mlx->win);
	mlx_destroy_display(cub->mlx->mlx);
	mlx_loop_end(cub->mlx->mlx);
	free(cub->mlx->mlx);
	free(cub->mlx);
}


void	exit_cub(t_cub *cub, int exit_num)
{

	
	if(exit_num != 51)
	{
		free_mlx(cub);
	}
	
	free_textures(cub);

	free_map(cub);

	free(cub->player);
	free(cub->ray);
	free(cub);

	exit(exit_num);
}

void	player_direction(t_cub *cub)
{
	cub->player->dir[_X_] = 0;
	cub->player->dir[_Y_] = -1;

	if (cub->map->map[cub->map->player_x][cub->map->player_y] == 'E')
	{
		rotate(&cub->player->dir[_X_], &cub->player->dir[_Y_], PI);
	    rotate(&cub->player->plane[_X_], &cub->player->plane[_Y_], PI);
	}
	else if (cub->map->map[cub->map->player_x][cub->map->player_y] == 'S')
	{
		rotate(&cub->player->dir[_X_], &cub->player->dir[_Y_], PI / 2);
	    rotate(&cub->player->plane[_X_], &cub->player->plane[_Y_], PI / 2);
	}
	else if (cub->map->map[cub->map->player_x][cub->map->player_y] == 'W')
	{
		rotate(&cub->player->dir[_X_], &cub->player->dir[_Y_], PI * 2);
	    rotate(&cub->player->plane[_X_], &cub->player->plane[_Y_], PI * 2);
		
	}
	else if (cub->map->map[cub->map->player_x][cub->map->player_y] == 'N')
	{
		rotate(&cub->player->dir[_X_], &cub->player->dir[_Y_],(PI * 3) / 2);
	    rotate(&cub->player->plane[_X_], &cub->player->plane[_Y_], (PI * 3) / 2);
	}
}

void	init_player(t_cub *cub)
{ 
	cub->player = malloc(sizeof(t_player));
	cub->ray = malloc(sizeof(t_raycasting));
	
	cub->player->pos[_X_] = (double)cub->map->player_x + COLISION_DIS;
	cub->player->pos[_Y_] = (double)cub->map->player_y + COLISION_DIS;
	cub->player->plane[_X_] = 0.66; 
	cub->player->plane[_Y_] = 0;

	player_direction(cub);

}