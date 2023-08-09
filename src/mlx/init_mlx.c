/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-s <jlucas-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 21:42:21 by jlucas-s          #+#    #+#             */
/*   Updated: 2023/08/09 19:08:17 by jlucas-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void get_colors(t_cub *cub, int tx)
{
	int x;
	int y;

    cub->tx_data[tx]->ptr = mlx_xpm_file_to_image(cub->mlx->mlx, cub->map->textures[tx], &cub->tx_data[tx]->largura, &cub->tx_data[tx]->altura);
    if(cub->tx_data[tx]->ptr == NULL)
        exit_cub(cub, 1);// corrigir
        
	cub->tx_data[tx]->data = (int *)mlx_get_data_addr(cub->tx_data[tx]->ptr, &cub->tx_data[tx]->bpp, &cub->tx_data[tx]->size_l, &cub->tx_data[tx]->endian);
    
	cub->tx_data[tx]->texture = (int **)malloc(sizeof(int *) * cub->tx_data[tx]->altura);
        
	y = -1;
	while(++y < cub->tx_data[tx]->altura)
    {
		cub->tx_data[tx]->texture[y] = (int *)malloc(sizeof(int) * cub->tx_data[tx]->largura);
   		x = -1;
		while(++x < cub->tx_data[tx]->largura)
			cub->tx_data[tx]->texture[y][x] = cub->tx_data[tx]->data[y * cub->tx_data[tx]->largura + x];
	}

    mlx_destroy_image(cub->mlx->mlx, cub->tx_data[tx]->ptr);
}

void init_mlx(t_cub *cub)
{
    cub->mlx = malloc(sizeof(t_mlx));
    cub->mlx->mlx = mlx_init();
    if (cub->mlx->mlx == NULL)
        exit_cub(cub, 51);
    cub->mlx->win = mlx_new_window(cub->mlx->mlx, 800, 600, "CUB3D");
    if (cub->mlx->win == NULL)
        exit_cub(cub, 81);
}

void init_img(t_cub *cub)
{
    int i;

    i = -1;
    while(++i < 4)
    {
        cub->tx_data[i] = malloc(sizeof(t_texture)); // DAR FREE
        get_colors(cub, i);
    }
    // printf("NO:%i\n,SO:%i\n,WE:%i\n.EA:%i\n", cub->img[NO]->texture[35][35],cub->img[SO]->texture[35][35],cub->img[WE]->texture[35][35],cub->img[EA]->texture[35][35]);
}
