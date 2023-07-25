/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dofranci <dofranci@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 21:30:17 by jlucas-s          #+#    #+#             */
/*   Updated: 2023/07/25 11:12:51 by dofranci         ###   ########.fr       */
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
	else if (keycode == W_KEY)
    {
        cub->posy -= 5;
    }
    else if (keycode == A_KEY)
    {
        cub->posx -= 5;
    }
	else if (keycode == S_KEY)
    {
        cub->posy += 5;
    }
	else if (keycode == D_KEY)
    {
        cub->posx += 5;
    }
    // mlx_clear_window(cub->mlx->mlx, cub->mlx->win);
    cub->mlx->img = mlx_new_image(cub->mlx->mlx, WIN_WIDTH, WIN_HEIGHT);
    cub->mlx->addr = mlx_get_data_addr(cub->mlx->img, &cub->mlx->bits_per_pixel, &cub->mlx->line_length, &cub->mlx->endian);
    floor_and_ceiling(cub);
    draw_player(cub, cub->posx, cub->posy);
    draw_map(cub, 1);
	mlx_put_image_to_window(cub->mlx->mlx, cub->mlx->win, cub->mlx->img, 0, 0);
    mlx_destroy_image(cub->mlx->mlx, cub->mlx->img);
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