/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dofranci <dofranci@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 18:20:46 by dofranci          #+#    #+#             */
/*   Updated: 2023/08/16 18:22:20 by dofranci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	rotate(double *x, double *y, double angle)
{
	double	s;
	double	c;
	double	new_x;
	double	new_y;

	s = sin(angle);
	c = cos(angle);
	new_x = *x * c - *y * s;
	new_y = *x * s + *y * c;
	*x = new_x;
	*y = new_y;
}

void	move_vertical(int keycode, t_cub *cub, double *strafedir)
{
	if (keycode == W_KEY)
	{
		if (cub->map->map[(int)(cub->player->pos[_X_] + \
		(cub->player->dir[_X_] * \
		COLISION_DIS))][(int)(cub->player->pos[_Y_] + \
		(cub->player->dir[_Y_] * COLISION_DIS))] != '1')
		{
			cub->player->pos[_X_] += cub->player->dir[_X_] * MOVE_SPEED;
			cub->player->pos[_Y_] += cub->player->dir[_Y_] * MOVE_SPEED;
		}
	}
	else if (keycode == S_KEY)
	{
		if (cub->map->map[(int)(cub->player->pos[_X_] - cub->player->dir[_X_] * \
		COLISION_DIS)][(int)(cub->player->pos[_Y_] - cub->player->dir[_Y_] * \
		COLISION_DIS)] != '1')
		{
			cub->player->pos[_X_] -= cub->player->dir[_X_] * MOVE_SPEED;
			cub->player->pos[_Y_] -= cub->player->dir[_Y_] * MOVE_SPEED;
		}
	}
}

void	move_horizontal(int keycode, t_cub *cub, double *strafedir)
{
	if (keycode == A_KEY)
	{
		if (cub->map->map[(int)(cub->player->pos[_X_] + (strafedir[_X_] * \
		COLISION_DIS))][(int)(cub->player->pos[_Y_] + (strafedir[_Y_] * \
		COLISION_DIS))] != '1')
		{
			cub->player->pos[_X_] += strafedir[_X_] * MOVE_SPEED;
			cub->player->pos[_Y_] += strafedir[_Y_] * MOVE_SPEED;
		}
	}
	else if (keycode == D_KEY)
	{
		if (cub->map->map[(int)(cub->player->pos[_X_] - (strafedir[_X_] * \
		COLISION_DIS))][(int)(cub->player->pos[_Y_] - (strafedir[_Y_] * \
		COLISION_DIS))] != '1')
		{
			cub->player->pos[_X_] -= strafedir[_X_] * MOVE_SPEED;
			cub->player->pos[_Y_] -= strafedir[_Y_] * MOVE_SPEED;
		}
	}
}
