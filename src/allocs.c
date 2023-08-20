/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-s <jlucas-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 21:57:56 by jlucas-s          #+#    #+#             */
/*   Updated: 2023/08/15 22:31:45 by jlucas-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_map(t_cub *cub, int exit_num)
{
	ft_freemtx(cub->map->textures_paths);
	ft_freemtx(cub->map->map);
	free(cub->map);
	if (exit_num != 0)
	{
		free(cub);
		exit(exit_num);
	}
}

void	free_textures(t_cub *cub)
{
	int	i;
	int	j;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < cub->tx_data[i]->height)
			free(cub->tx_data[i]->texture[j]);
		free(cub->tx_data[i]->texture);
	}
	i = -1;
	while (++i < 4)
		free(cub->tx_data[i]);
}

void	free_mlx(t_cub *cub)
{
	mlx_destroy_window(cub->mlx->mlx, cub->mlx->win);
	mlx_destroy_display(cub->mlx->mlx);
	mlx_loop_end(cub->mlx->mlx);
	free(cub->mlx->mlx);
	free(cub->mlx);
}

void	exit_cub(t_cub *cub, int exit_num)
{
	int	multiplier;

	multiplier = 1;
	if (exit_num >= 0)
	{
		free_mlx(cub);
		multiplier = -1;
	}
	free_textures(cub);
	free_map(cub, 0);
	free(cub->player);
	free(cub->ray);
	free(cub);
	exit(exit_num * multiplier);
}
