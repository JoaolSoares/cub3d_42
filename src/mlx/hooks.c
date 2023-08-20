/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-s <jlucas-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 21:30:17 by jlucas-s          #+#    #+#             */
/*   Updated: 2023/08/17 21:25:04 by jlucas-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	key_hook(int keycode, t_cub *cub)
{
	double	strafedir[2];

	strafedir[0] = cub->player->dir[_X_];
	strafedir[1] = cub->player->dir[_Y_];
	rotate(&strafedir[_X_], &strafedir[_Y_], PI / 2);
	if (keycode == ESC_KEY)
		exit_cub(cub, 0);
	else if (keycode == W_KEY || keycode == S_KEY)
		move_vertical(keycode, cub);
	else if (keycode == A_KEY || keycode == D_KEY)
		move_horizontal(keycode, cub, strafedir);
	else if (keycode == LEFT_KEY)
	{
		rotate(&cub->player->dir[_X_], &cub->player->dir[_Y_], ROTATE_SPEED);
		rotate(&cub->player->plane[_X_], &cub->player->plane[_Y_], \
		ROTATE_SPEED);
	}
	else if (keycode == RIGHT_KEY)
	{
		rotate(&cub->player->dir[_X_], &cub->player->dir[_Y_], -ROTATE_SPEED);
		rotate(&cub->player->plane[_X_], &cub->player->plane[_Y_], \
		-ROTATE_SPEED);
	}
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
