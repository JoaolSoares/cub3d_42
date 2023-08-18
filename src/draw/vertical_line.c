/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-s <jlucas-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 19:38:56 by jlucas-s          #+#    #+#             */
/*   Updated: 2023/08/17 22:20:07 by jlucas-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	tex_y_calculate(t_cub *cub)
{
	cub->ray->tex[_Y_] = (((int)cub->ray->line_start - WIN_HEIGHT / 2 + \
	cub->ray->wall_line_height / 2) * \
	cub->tx_data[cub->ray->tex_side]->height) / cub->ray->wall_line_height;
	if ((int)cub->ray->tex[_Y_] > cub->tx_data[1]->height)
		cub->ray->tex[_Y_] = cub->tx_data[1]->height;
	else if (cub->ray->tex[_Y_] < 0)
		cub->ray->tex[_Y_] = 0;
}

static void	draw_line(t_cub *cub, int x)
{
	int		end_copy;

	end_copy = (int)cub->ray->line_end;
	while ((int)cub->ray->line_start != (int)cub->ray->line_end)
	{
		tex_y_calculate(cub);
		if (cub->ray->tex[_X_] < cub->tx_data[cub->ray->tex_side]->width && \
		cub->ray->tex[_Y_] < cub->tx_data[cub->ray->tex_side]->height)
		{
			if ((int)cub->ray->line_start < (int)cub->ray->line_end)
				pixel_put(cub, x, (int)cub->ray->line_start++, \
				cub->tx_data[cub->ray->tex_side]->texture[cub->ray->tex[_Y_]] \
				[cub->ray->tex[_X_]]);
			else
			{
				pixel_put(cub, x, (int)cub->ray->line_start - \
				((int)cub->ray->line_start - end_copy), \
				cub->tx_data [cub->ray->tex_side]->texture[cub->ray->tex[_Y_]] \
				[cub->ray->tex[_X_]]);
				cub->ray->line_start--;
				end_copy++;
			}
		}
	}
}

static void	tex_x_calculate(t_cub *cub)
{
	cub->ray->tex[_X_] = \
	(int)(cub->ray->wall_x * (float)cub->tx_data[cub->ray->tex_side]->width);
	if ((int)cub->ray->tex[_X_] > cub->tx_data[1]->width)
		cub->ray->tex[_X_] = cub->tx_data[1]->width;
	else if (cub->ray->tex[_X_] < 0)
		cub->ray->tex[_X_] = 0;
	if ((cub->ray->hit_side == _X_ && (cub->ray->ray_dir[_X_]) > 0) || \
	(cub->ray->hit_side == _Y_ && (cub->ray->ray_dir[_Y_]) < 0))
		cub->ray->tex[_X_] = \
		cub->tx_data[cub->ray->tex_side]->width - cub->ray->tex[_X_] - 1;
}

static void	get_tex_side(t_cub *cub)
{
	if (cub->ray->hit_side == _Y_ && cub->ray->ray_dir[_Y_] < 0)
		cub->ray->tex_side = EA;
	else if (cub->ray->hit_side == _Y_ && cub->ray->ray_dir[_Y_] > 0)
		cub->ray->tex_side = WE;
	else if (cub->ray->hit_side == _X_ && cub->ray->ray_dir[_X_] < 0)
		cub->ray->tex_side = SO;
	else if (cub->ray->hit_side == _X_ && cub->ray->ray_dir[_X_] > 0)
		cub->ray->tex_side = NO;
}

void	draw_vertical_line(t_cub *cub, int x)
{
	get_tex_side(cub);
	if ((cub->ray->hit_side == _X_ && cub->ray->ray_dir[_X_] < 0) || \
	(cub->ray->hit_side == _Y_ && cub->ray->ray_dir[_Y_] < 0))
	{
		cub->ray->ray_dir[_X_] *= -1;
		cub->ray->ray_dir[_Y_] *= -1;
	}
	if (cub->ray->hit_side == _X_)
		cub->ray->wall_x = cub->player->pos[_Y_] + \
		cub->ray->perpendicular_dist * (cub->ray->ray_dir[_Y_]);
	else
		cub->ray->wall_x = cub->player->pos[_X_] + \
		cub->ray->perpendicular_dist * (cub->ray->ray_dir[_X_]);
	cub->ray->wall_x -= (int)floor(cub->ray->wall_x);
	tex_x_calculate(cub);
	draw_line(cub, x);
}
