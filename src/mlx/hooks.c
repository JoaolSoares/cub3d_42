/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-s <jlucas-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 21:30:17 by jlucas-s          #+#    #+#             */
/*   Updated: 2023/08/02 22:23:27 by jlucas-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

// int	key_hook(int keycode, t_cub *cub)
// {
// 	if (keycode == ESC_KEY)
// 		exit_cub(cub, 0);
// 	else if (keycode == W_KEY)
//     {
//         if (cub->map->map[cub->map->player_x - 1][cub->map->player_y] != '1')
//             cub->map->player_x--;
//     }
//     else if (keycode == A_KEY)
//     {
//         if (cub->map->map[cub->map->player_x][cub->map->player_y - 1] != '1')
//             cub->map->player_y--;
//     }
// 	else if (keycode == S_KEY)
//     {
//         if (cub->map->map[cub->map->player_x + 1][cub->map->player_y] != '1')
//             cub->map->player_x++;
//     }
// 	else if (keycode == D_KEY)
//     {
//         if (cub->map->map[cub->map->player_x][cub->map->player_y + 1] != '1')
//             cub->map->player_y++;
//     }
//     // int i = -1;
//     // while (cub->map->map[++i])
//     // {
//     //     ft_printf("%s\n", cub->map->map[i]);
//     // }
//     // ft_printf("x = %i\ny = %i\n", cub->map->player_x, cub->map->player_y);
//     // ft_printf("----------------\n");

// 	// mlx_destroy_image(fdf->mlx, fdf->img);
// 	// draw(fdf);
// 	return (0);
// }

int	key_hook(int keycode, t_cub *cub)
{
	if (keycode == ESC_KEY)
		exit_cub(cub, 0);
	// else if (keycode == W_KEY)
    // {
    //     cub->player->posx += cub->player->deltaPosX;
    //     cub->player->posy += cub->player->deltaPosY;
    // }
    // // else if (keycode == A_KEY)
    // // {
    // //     cub->player->posx += cub->player->deltaPosX;
    // //     // cub->player->posy -= cub->player->deltaPosY;
    // // }
	// else if (keycode == S_KEY)
    // {
    //     cub->player->posx -= cub->player->deltaPosX;
    //     cub->player->posy -= cub->player->deltaPosY;
    // }
	// else if (keycode == D_KEY)
    // {
    //     // cub->player->posx -= cub->player->deltaPosX;
    //     // cub->player->posy += cub->player->deltaPosX;
    // }
    // else if (keycode == LEFT_KEY )
    // {
    //     cub->player->deltaPosA -= 0.25;
    //     if (cub->player->deltaPosA < 0)
    //         cub->player->deltaPosA += 2 * PI;
    //     cub->player->deltaPosX = cos(cub->player->deltaPosA) * 5;
    //     cub->player->deltaPosY = sin(cub->player->deltaPosA) * 5;
    // }
    // else if (keycode == RIGHT_KEY)
    // {
    //     cub->player->deltaPosA += 0.25;
    //     if (cub->player->deltaPosA > 2 * PI)
    //         cub->player->deltaPosA -= 2 * PI;
    //     cub->player->deltaPosX = cos(cub->player->deltaPosA) * 5;
    //     cub->player->deltaPosY = sin(cub->player->deltaPosA) * 5;
    // }
    cub->mlx->img = mlx_new_image(cub->mlx->mlx, WIN_WIDTH, WIN_HEIGHT);
    cub->mlx->addr = mlx_get_data_addr(cub->mlx->img, &cub->mlx->bits_per_pixel, &cub->mlx->line_length, &cub->mlx->endian);
    draw(cub);
    return (0);
}

static int	x_hook(t_cub *cub)
{
    exit_cub(cub, 0);
    return (0);
}

void	hook_handler(t_cub *cub)
{
    mlx_hook(cub->mlx->win, KeyPress, KeyPressMask, key_hook, cub);
	mlx_hook(cub->mlx->win, DestroyNotify, NoEventMask, x_hook, cub);
    mlx_loop(cub->mlx->mlx);
    mlx_loop_hook(cub->mlx->mlx, x_hook, cub);
}