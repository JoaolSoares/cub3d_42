/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-s <jlucas-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 19:34:15 by jlucas-s          #+#    #+#             */
/*   Updated: 2023/08/15 22:39:50 by jlucas-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	line_calculate(t_cub *cub)
{
	if (cub->ray->hit_side == _X_)
	{
		cub->ray->perpendicular_dist = fabs(cub->ray->wall_map_pos[_X_] \
		- cub->player->pos[_X_] + ((1 - cub->ray->step[_X_]) / 2)) \
		/ cub->ray->ray_dir[_X_];
	}
	else
	{
		cub->ray->perpendicular_dist = fabs(cub->ray->wall_map_pos[_Y_] \
		- cub->player->pos[_Y_] + ((1 - cub->ray->step[_Y_]) / 2)) \
		/ cub->ray->ray_dir[_Y_];
	}
	cub->ray->wall_line_height = WIN_HEIGHT / cub->ray->perpendicular_dist;
	cub->ray->line_start = WIN_HEIGHT / 2 - cub->ray->wall_line_height / 2;
	cub->ray->line_end = WIN_HEIGHT / 2 + cub->ray->wall_line_height / 2;
}

static void	dda_algorithm(t_cub *cub)
{
	cub->ray->dda_line_size[_X_] = cub->ray->dist_to_side[_X_];
	cub->ray->dda_line_size[_Y_] = cub->ray->dist_to_side[_Y_];
	cub->ray->wall_map_pos[_X_] = cub->ray->map_pos[_X_];
	cub->ray->wall_map_pos[_Y_] = cub->ray->map_pos[_Y_];
	cub->ray->hit = FALSE;
	while (cub->ray->hit == FALSE)
	{
		if (cub->ray->dda_line_size[_X_] < cub->ray->dda_line_size[_Y_])
		{
			cub->ray->wall_map_pos[_X_] += cub->ray->step[_X_];
			cub->ray->dda_line_size[_X_] += cub->ray->delta_dist[_X_];
			cub->ray->hit_side = _X_;
		}
		else
		{
			cub->ray->wall_map_pos[_Y_] += cub->ray->step[_Y_];
			cub->ray->dda_line_size[_Y_] += cub->ray->delta_dist[_Y_];
			cub->ray->hit_side = _Y_;
		}
		if (cub->map->map \
		[(int)cub->ray->wall_map_pos[_X_]][(int)cub->ray->wall_map_pos[_Y_]] \
		== '1')
			cub->ray->hit = TRUE;
	}
}

static void	dist_to_side_calculate(t_cub *cub)
{
	if (cub->ray->ray_dir[_X_] < 0)
	{
		cub->ray->dist_to_side[_X_] = (cub->player->pos[_X_] - \
		cub->ray->map_pos[_X_]) * cub->ray->delta_dist[_X_];
		cub->ray->step[_X_] = -1;
	}
	else
	{
		cub->ray->dist_to_side[_X_] = (cub->ray->map_pos[_X_] + 1 - \
		cub->player->pos[_X_]) * cub->ray->delta_dist[_X_];
		cub->ray->step[_X_] = 1;
	}
	if (cub->ray->ray_dir[_Y_] < 0)
	{
		cub->ray->dist_to_side[_Y_] = (cub->player->pos[_Y_] - \
		cub->ray->map_pos[_Y_]) * cub->ray->delta_dist[_Y_];
		cub->ray->step[_Y_] = -1;
	}
	else
	{
		cub->ray->dist_to_side[_Y_] = (cub->ray->map_pos[_Y_] + 1 - \
		cub->player->pos[_Y_]) * cub->ray->delta_dist[_Y_];
		cub->ray->step[_Y_] = 1;
	}
}

static void	deltadist_calculate(t_cub *cub)
{
	if (cub->ray->ray_dir[_X_] == 0)
	{
		cub->ray->delta_dist[_X_] = 1;
		cub->ray->delta_dist[_Y_] = 0;
	}
	else
	{
		if (cub->ray->ray_dir[_Y_] != 0)
			cub->ray->delta_dist[_X_] = fabs(1 / cub->ray->ray_dir[_X_]);
	}
	if (cub->ray->ray_dir[_Y_] == 0)
	{
		cub->ray->delta_dist[_Y_] = 1;
		cub->ray->delta_dist[_X_] = 0;
	}
	else
	{
		if (cub->ray->ray_dir[_X_] != 0)
			cub->ray->delta_dist[_Y_] = fabs(1 / cub->ray->ray_dir[_Y_]); 
	}
}

void	raycasting(t_cub *cub)
{
	double			pixel_x;

	pixel_x = 0;
	while (pixel_x <= WIN_WIDTH)
	{
		cub->ray->multiplier = 2 * (pixel_x / WIN_WIDTH) - 1;
		cub->ray->camera_pixel[_X_] = \
		cub->player->plane[_X_] * cub->ray->multiplier;
		cub->ray->camera_pixel[_Y_] = \
		cub->player->plane[_Y_] * cub->ray->multiplier;
		cub->ray->ray_dir[_X_] = \
		cub->player->dir[_X_] + cub->ray->camera_pixel[_X_];
		cub->ray->ray_dir[_Y_] = \
		cub->player->dir[_Y_] + cub->ray->camera_pixel[_Y_];
		deltadist_calculate(cub);
		cub->ray->map_pos[_X_] = floor(cub->player->pos[_X_]);
		cub->ray->map_pos[_Y_] = floor(cub->player->pos[_Y_]);
		dist_to_side_calculate(cub);
		dda_algorithm(cub);
		line_calculate(cub);
		draw_vertical_line(cub, WIN_WIDTH - pixel_x, \
		(int)cub->ray->line_start, (int)cub->ray->line_end);
		pixel_x++;
	}
}
