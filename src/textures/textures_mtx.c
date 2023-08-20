/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_mtx.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-s <jlucas-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 23:05:48 by jlucas-s          #+#    #+#             */
/*   Updated: 2023/08/16 19:21:41 by jlucas-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	tx_file_error(t_cub *cub, int tx)
{
	int	y;

	ft_putstr_fd("Error\nInvalid textures path\n", \
	STDERR_FILENO);
	free_map(cub, 0);
	free(cub->tx_data[tx]);
	while (--tx >= 0)
	{
		y = -1;
		while (++y < cub->tx_data[tx]->height)
			free(cub->tx_data[tx]->texture[y]);
		free(cub->tx_data[tx]->texture);
		free(cub->tx_data[tx]);
	}
	free_mlx(cub);
	free(cub);
	exit(131);
}

static void	get_textures(t_cub *cub, int tx)
{
	int	x;
	int	y;

	cub->tx_data[tx]->ptr = mlx_xpm_file_to_image(cub->mlx->mlx, \
	cub->map->textures_paths[tx], &cub->tx_data[tx]->width, \
	&cub->tx_data[tx]->height);
	if (cub->tx_data[tx]->ptr == NULL)
		tx_file_error(cub, tx);
	cub->tx_data[tx]->data = (int *)mlx_get_data_addr(cub->tx_data[tx]->ptr, \
	&cub->tx_data[tx]->bpp, &cub->tx_data[tx]->size_l, \
	&cub->tx_data[tx]->endian);
	cub->tx_data[tx]->texture = \
	malloc(sizeof(int *) * cub->tx_data[tx]->height);
	y = -1;
	while (++y < cub->tx_data[tx]->height)
	{
		cub->tx_data[tx]->texture[y] = \
		(int *)malloc(sizeof(int) * cub->tx_data[tx]->width);
		x = -1;
		while (++x < cub->tx_data[tx]->width)
			cub->tx_data[tx]->texture[y][x] = \
			cub->tx_data[tx]->data[y * cub->tx_data[tx]->width + x];
	}
	mlx_destroy_image(cub->mlx->mlx, cub->tx_data[tx]->ptr);
}

void	init_textures(t_cub *cub)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		cub->tx_data[i] = malloc(sizeof(t_texture));
		get_textures(cub, i);
		i++;
	}
}
