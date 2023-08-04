/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-s <jlucas-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 21:30:17 by jlucas-s          #+#    #+#             */
/*   Updated: 2023/08/04 17:31:45 by jlucas-s         ###   ########.fr       */
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

void rotate(double *x, double *y, double angle) {
    double s = sin(angle);
    double c = cos(angle);

    double new_x = *x * c - *y * s;
    double new_y = *x * s + *y * c;

    *x = new_x;
    *y = new_y;
}

int	key_hook(int keycode, t_cub *cub)
{
    double strafeDir[2];
    
	if (keycode == ESC_KEY)
		exit_cub(cub, 0);
	else if (keycode == W_KEY)
    {
        if (cub->map->map[(int)(cub->player->posx)][(int)(cub->player->posy + 0.1)] != '1')
            cub->player->posx += cub->player->dirX * MOVE_SPEED;
            cub->player->posy += cub->player->dirY * MOVE_SPEED;
    }
    else if (keycode == A_KEY)
    {
        if (cub->map->map[(int)(cub->player->posx + 0.1)][(int)(cub->player->posy)] != '1')
            strafeDir[0] = cub->player->dirX;
            strafeDir[1] = cub->player->dirY;
            rotate(&strafeDir[0], &strafeDir[1], PI/2);
            cub->player->posx -= strafeDir[0] * MOVE_SPEED;
            cub->player->posy -= strafeDir[1] * MOVE_SPEED;
    }
	else if (keycode == S_KEY)
    {
        if (cub->map->map[(int)(cub->player->posx)][(int)(cub->player->posy - 0.1)] != '1')
            cub->player->posx -= cub->player->dirX * MOVE_SPEED;
            cub->player->posy -= cub->player->dirY * MOVE_SPEED;
    }
	else if (keycode == D_KEY)
    {
        if (cub->map->map[(int)(cub->player->posx - 0.1)][(int)(cub->player->posy)] != '1')
            strafeDir[0] = cub->player->dirX;
            strafeDir[1] = cub->player->dirY;
            rotate(&strafeDir[0], &strafeDir[1], PI/2);
            cub->player->posx += strafeDir[0] * MOVE_SPEED;
            cub->player->posy += strafeDir[1] * MOVE_SPEED;
    }
    else if (keycode == LEFT_KEY )
    {
        rotate(&cub->player->dirX, &cub->player->dirY, -0.1);
	    rotate(&cub->player->planeX, &cub->player->planeY, -0.1);
    }
    else if (keycode == RIGHT_KEY)
    {
        rotate(&cub->player->dirX, &cub->player->dirY, 0.1);
	    rotate(&cub->player->planeX, &cub->player->planeY, 0.1);
    }
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