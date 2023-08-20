/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-s <jlucas-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 18:20:46 by dofranci          #+#    #+#             */
/*   Updated: 2023/08/20 19:45:24 by jlucas-s         ###   ########.fr       */
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

static int	can_move_vertical(t_cub *cub, int keycode)
{
	double	colision_ray;

	colision_ray = COLISION_DIS / 50;
	while (colision_ray < COLISION_DIS)
	{
		if (keycode == W_KEY && \
		cub->map->map[(int)(cub->player->pos[_X_] + (cub->player->dir[_X_] * \
		colision_ray))][(int)(cub->player->pos[_Y_] + \
		(cub->player->dir[_Y_] * colision_ray))] == '1')
			return (FALSE);
		else if (keycode == S_KEY && \
		cub->map->map[(int)(cub->player->pos[_X_] - cub->player->dir[_X_] * \
		colision_ray)][(int)(cub->player->pos[_Y_] - cub->player->dir[_Y_] * \
		colision_ray)] == '1')
			return (FALSE);
		colision_ray += COLISION_DIS / 50;
	}
	return (TRUE);
}

void	move_vertical(int keycode, t_cub *cub)
{
	if (keycode == W_KEY)
	{
		if (cub->map->map[(int)(cub->player->pos[_X_] + \
		(cub->player->dir[_X_] * \
		COLISION_DIS))][(int)(cub->player->pos[_Y_] + \
		(cub->player->dir[_Y_] * COLISION_DIS))] != '1' && \
		can_move_vertical(cub, keycode))
		{
			cub->player->pos[_X_] += cub->player->dir[_X_] * MOVE_SPEED;
			cub->player->pos[_Y_] += cub->player->dir[_Y_] * MOVE_SPEED;
		}
	}
	else if (keycode == S_KEY)
	{
		if (cub->map->map[(int)(cub->player->pos[_X_] - cub->player->dir[_X_] * \
		COLISION_DIS)][(int)(cub->player->pos[_Y_] - cub->player->dir[_Y_] * \
		COLISION_DIS)] != '1' && can_move_vertical(cub, keycode))
		{
			cub->player->pos[_X_] -= cub->player->dir[_X_] * MOVE_SPEED;
			cub->player->pos[_Y_] -= cub->player->dir[_Y_] * MOVE_SPEED;
		}
	}
}

static int	can_move_horizontal(t_cub *cub, double *strafedir, int keycode)
{
	double	colision_ray;

	colision_ray = COLISION_DIS / 50;
	while (colision_ray < COLISION_DIS)
	{
		if (keycode == A_KEY && \
		cub->map->map[(int)(cub->player->pos[_X_] + (strafedir[_X_] * \
		colision_ray))][(int)(cub->player->pos[_Y_] + (strafedir[_Y_] * \
		colision_ray))] == '1')
			return (FALSE);
		else if (keycode == D_KEY && \
		cub->map->map[(int)(cub->player->pos[_X_] - (strafedir[_X_] * \
		colision_ray))][(int)(cub->player->pos[_Y_] - (strafedir[_Y_] * \
		colision_ray))] == '1')
			return (FALSE);
		colision_ray += COLISION_DIS / 50;
	}
	return (TRUE);
}

void	move_horizontal(int keycode, t_cub *cub, double *strafedir)
{
	if (keycode == A_KEY)
	{
		if (cub->map->map[(int)(cub->player->pos[_X_] + (strafedir[_X_] * \
		COLISION_DIS))][(int)(cub->player->pos[_Y_] + (strafedir[_Y_] * \
		COLISION_DIS))] != '1' && can_move_horizontal(cub, strafedir, keycode))
		{
			cub->player->pos[_X_] += strafedir[_X_] * MOVE_SPEED;
			cub->player->pos[_Y_] += strafedir[_Y_] * MOVE_SPEED;
		}
	}
	else if (keycode == D_KEY)
	{
		if (cub->map->map[(int)(cub->player->pos[_X_] - (strafedir[_X_] * \
		COLISION_DIS))][(int)(cub->player->pos[_Y_] - (strafedir[_Y_] * \
		COLISION_DIS))] != '1' && can_move_horizontal(cub, strafedir, keycode))
		{
			cub->player->pos[_X_] -= strafedir[_X_] * MOVE_SPEED;
			cub->player->pos[_Y_] -= strafedir[_Y_] * MOVE_SPEED;
		}
	}
}
