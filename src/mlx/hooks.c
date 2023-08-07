/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-s <jlucas-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 21:30:17 by jlucas-s          #+#    #+#             */
/*   Updated: 2023/08/07 19:37:51 by jlucas-s         ###   ########.fr       */
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

void    rotate(double *x, double *y, double angle)
{
    double  s;
    double  c;

    s = sin(angle);
    c = cos(angle);

    double new_x = *x * c - *y * s;
    double new_y = *x * s + *y * c;

    *x = new_x;
    *y = new_y;
}

int	key_hook(int keycode, t_cub *cub)
{
    double strafeDir[2];

    strafeDir[0] = cub->player->dir[_X_];
    strafeDir[1] = cub->player->dir[_Y_];
    rotate(&strafeDir[_X_], &strafeDir[_Y_], PI/2);

	if (keycode == ESC_KEY)
		exit_cub(cub, 0);
	else if (keycode == W_KEY)
    {
        if (cub->map->map[(int)(cub->player->pos[_X_] + (cub->player->dir[_X_] * COLISION_DIS))][(int)(cub->player->pos[_Y_] + (cub->player->dir[_Y_] * COLISION_DIS))] != '1')
        {
            cub->player->pos[_X_] += cub->player->dir[_X_] * MOVE_SPEED;
            cub->player->pos[_Y_] += cub->player->dir[_Y_] * MOVE_SPEED;
        }
    }
    else if (keycode == A_KEY)
    {
        if (cub->map->map[(int)(cub->player->pos[_X_] + (strafeDir[_X_] * COLISION_DIS))][(int)(cub->player->pos[_Y_] + (strafeDir[_Y_] * COLISION_DIS))] != '1')
        {
            cub->player->pos[_X_] += strafeDir[_X_] * MOVE_SPEED;
            cub->player->pos[_Y_] += strafeDir[_Y_] * MOVE_SPEED;
        }
    }
	else if (keycode == S_KEY)
    {
        if (cub->map->map[(int)(cub->player->pos[_X_] - cub->player->dir[_X_] * COLISION_DIS)][(int)(cub->player->pos[_Y_] - cub->player->dir[_Y_] * COLISION_DIS)] != '1')
        {
            cub->player->pos[_X_] -= cub->player->dir[_X_] * MOVE_SPEED;
            cub->player->pos[_Y_] -= cub->player->dir[_Y_] * MOVE_SPEED;
        }
    }
	else if (keycode == D_KEY)
    {
        if (cub->map->map[(int)(cub->player->pos[_X_] - (strafeDir[_X_] * COLISION_DIS))][(int)(cub->player->pos[_Y_] - (strafeDir[_Y_] * COLISION_DIS))] != '1')
        {
            cub->player->pos[_X_] -= strafeDir[_X_] * MOVE_SPEED;
            cub->player->pos[_Y_] -= strafeDir[_Y_] * MOVE_SPEED;
        }
    }
    else if (keycode == LEFT_KEY )
    {
        rotate(&cub->player->dir[_X_], &cub->player->dir[_Y_], ROTATE_SPEED);
	    rotate(&cub->player->plane[_X_], &cub->player->plane[_Y_], ROTATE_SPEED);
    }
    else if (keycode == RIGHT_KEY)
    {
        rotate(&cub->player->dir[_X_], &cub->player->dir[_Y_], -ROTATE_SPEED);
	    rotate(&cub->player->plane[_X_], &cub->player->plane[_Y_], -ROTATE_SPEED);
    }
    draw(cub);
    return (0);
}

static int	x_hook(t_cub *cub)
{
    exit_cub(cub, 0);
    return (0);
}

// bonus
// static int  mouse_hook(int x, int y, t_cub *cub)
// {
//     static int old_x;
    

//     printf("accelera = %i\n", (x - old_x));
//     if (x > old_x)
//     {
//         rotate(&cub->player->dir[_X_], &cub->player->dir[_Y_], -ROTATE_SPEED );
// 	    rotate(&cub->player->plane[_X_], &cub->player->plane[_Y_], -ROTATE_SPEED);
//     }
//     if (x < old_x)
//     {
//         rotate(&cub->player->dir[_X_], &cub->player->dir[_Y_], ROTATE_SPEED);
// 	    rotate(&cub->player->plane[_X_], &cub->player->plane[_Y_], ROTATE_SPEED);
//     }
//     old_x = x;
//     draw(cub);
// }
// bonus

void	hook_handler(t_cub *cub)
{
    mlx_hook(cub->mlx->win, KeyPress, KeyPressMask, key_hook, cub);
    // mlx_hook(cub->mlx->win, MotionNotify, PointerMotionMask, mouse_hook, cub);
	mlx_hook(cub->mlx->win, DestroyNotify, NoEventMask, x_hook, cub);
    mlx_loop(cub->mlx->mlx);
    mlx_loop_hook(cub->mlx->mlx, x_hook, cub);
}