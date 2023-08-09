/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-s <jlucas-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 21:42:21 by jlucas-s          #+#    #+#             */
/*   Updated: 2023/08/05 16:02:17 by jlucas-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int **get_colors(t_cub *cub, int tx)
{
	int **buffer;
	int x;
	int y;
	int pixel_index;

    cub->img[tx]->ptr = mlx_xpm_file_to_image(cub->mlx->mlx, cub->map->textures[tx], &cub->img[tx]->largura, &cub->img[tx]->altura);
    if(cub->img[tx]->ptr == NULL)
        exit_cub(cub, 1);// corrigir
	cub->img[tx]->data = (int *)mlx_get_data_addr(cub->img[tx]->ptr, &cub->img[tx]->bpp, &cub->img[tx]->size_l, &cub->img[tx]->endian);
	buffer = (int **)malloc(sizeof(int *) * cub->img[tx]->altura);
    if(buffer == NULL)
        exit_cub(cub, 1);// corrigir
	y = -1;
	while(++y < cub->img[tx]->altura)
    {
		buffer[y] = (int *)malloc(sizeof(int) * cub->img[tx]->largura);
        if(buffer[y] == NULL)
            exit_cub(cub, 1);// corrigir
   		x = -1;
		while(++x < cub->img[tx]->largura)
		{
			pixel_index = y * cub->img[tx]->largura + x;
			buffer[y][x] = cub->img[tx]->data[pixel_index];
		}
	}
	// printf("pixel_color=%i\n", buffer[63][35]);
	// y = -1;
	// while (++y < cub->img[tx]->altura)
	// free(buffer[y]);
	// free(buffer);
    mlx_destroy_image(cub->mlx->mlx, cub->img[tx]->ptr);
    printf("NO:%i\n", cub->img[NO]->texture[35][35]);

	return (buffer);
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
    int count;

    count = -1;
    while(++count < 4)
    {
        cub->img[count] = malloc(sizeof(t_img)); // DAR FREE
        get_colors(cub, count);
    }
    // printf("NO:%i\n,SO:%i\n,WE:%i\n.EA:%i\n", cub->img[NO]->texture[35][35],cub->img[SO]->texture[35][35],cub->img[WE]->texture[35][35],cub->img[EA]->texture[35][35]);
}
