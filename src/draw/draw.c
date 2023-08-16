/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-s <jlucas-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 19:44:21 by jlucas-s          #+#    #+#             */
/*   Updated: 2023/08/15 22:45:00 by jlucas-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	pixel_put(t_cub *cub, int x, int y, int color)
{
	char	*dst;

	if (x < 0)
		x = 0;
	if (y < 0)
		y = 0;
	if (x > WIN_WIDTH)
		x = WIN_WIDTH;
	if (y > WIN_HEIGHT)
		y = WIN_HEIGHT;
	dst = cub->mlx->addr + (y * cub->mlx->line_length + x * (cub->mlx->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

static void	floor_and_ceiling(t_cub *cub)
{
	int x;
	int y;

	x = 0;
	while(x++ < WIN_WIDTH)
	{
		y = 0;
		while(y++ < WIN_HEIGHT / 2)
			pixel_put(cub, x, y, cub->map->ceil_color);
	}
	x = 0;
	while(x++ < WIN_WIDTH)
	{
		y = WIN_HEIGHT / 2;
		while(y++ < WIN_HEIGHT)
			pixel_put(cub, x, y, cub->map->floor_color);
	}
}

void	draw_vertical_line(t_cub *cub, int x, int y1, int y2)
{
	float	wallX;
	int		texX;
	int		texY;
	int		d;
	int		tx_side;
	int		mult;

	mult = 1;
	if (cub->ray->hit_side == _Y_ && cub->ray->ray_dir[_Y_] < 0)
	{
		tx_side = EA;
		mult = -1;
	}
	else if(cub->ray->hit_side == _Y_ && cub->ray->ray_dir[_Y_] > 0)
		tx_side = WE;
	else if(cub->ray->hit_side == _X_ && cub->ray->ray_dir[_X_] < 0)
	{
		tx_side = SO;
		mult = -1;
	}
	else if(cub->ray->hit_side == _X_ && cub->ray->ray_dir[_X_] > 0)
		tx_side = NO;

	if (cub->ray->hit_side == _X_)
		wallX = cub->player->pos[_Y_] + cub->ray->perpendicular_dist * (cub->ray->ray_dir[_Y_] * mult);
	else
		wallX = cub->player->pos[_X_] + cub->ray->perpendicular_dist * (cub->ray->ray_dir[_X_] * mult);
	wallX -= (int)floor(wallX);
	
	texX = (int)(wallX * (float)cub->tx_data[tx_side]->width);
    if((int)texX > cub->tx_data[1]->width)
        texX = cub->tx_data[1]->width;
	else if(texX < 0)
        texX = 0;
	if ((cub->ray->hit_side == _X_ && (cub->ray->ray_dir[_X_] * mult) > 0) || (cub->ray->hit_side == _Y_ && (cub->ray->ray_dir[_Y_] * mult) < 0))
		texX = cub->tx_data[tx_side]->width - texX - 1;
	while (y1 < y2)
	{
		texY = ((y1 - WIN_HEIGHT / 2 + cub->ray->wall_line_height / 2) * cub->tx_data[tx_side]->height) / cub->ray->wall_line_height;
		if((int)texY > cub->tx_data[1]->height)
            texY = cub->tx_data[1]->height;
		else if(texY < 0)
			texY = 0;
		if (texX < cub->tx_data[tx_side]->width && texY < cub->tx_data[tx_side]->height)
			pixel_put(cub, x, y1, cub->tx_data[tx_side]->texture[texY][texX]);
		y1++;
	}
	int fodace = y2;
	while (y1 > y2)
	{
		texY = ((y1 - WIN_HEIGHT / 2 + cub->ray->wall_line_height / 2) * cub->tx_data[tx_side]->height) / cub->ray->wall_line_height;
		if((int)texY > cub->tx_data[1]->height)
            texY = cub->tx_data[1]->height;
		else if(texY < 0)
			texY = 0;
		if (texX < cub->tx_data[tx_side]->width && texY < cub->tx_data[tx_side]->height)
			pixel_put(cub, x, y1 - (y1 - fodace), cub->tx_data[tx_side]->texture[texY][texX]);
		y1--;
		fodace++;
	}
}

void	draw(t_cub *cub)
{
	cub->mlx->img = mlx_new_image(cub->mlx->mlx, WIN_WIDTH, WIN_HEIGHT);
    cub->mlx->addr = mlx_get_data_addr(cub->mlx->img, &cub->mlx->bits_per_pixel, \
	&cub->mlx->line_length, &cub->mlx->endian);
	floor_and_ceiling(cub);
	raycasting(cub);
	mlx_put_image_to_window(cub->mlx->mlx, cub->mlx->win, cub->mlx->img, 0, 0);
	mlx_destroy_image(cub->mlx->mlx, cub->mlx->img);
}



// void draw_square(t_cub *cub, int x, int y, int size)
// {
// 		int tempy;
// 		int tempx;
// 		int color; 

// 		color = 0xFFFFFF;
// 		if(size != 16)
// 			color = 0x008000;
// 		tempy = y;
// 		tempx = x;
// 		while(x++ < (tempx + size))
// 		{
// 			y = tempy;
// 			while(y++ < (tempy + size))
// 				pixel_put(cub, x, y, color);
// 		}
// }

// void draw_map(t_cub *cub)
// {
// 		int x;
// 		int y;
	
// 		x = 0;
// 		y = 0;
// 		while(cub->map->map[y])
// 		{
// 			x = 0;
// 			while(cub->map->map[y][x])
// 			{
// 				if(cub->map->map[y][x] == '1')
// 					draw_square(cub, (x * 16), (y * 16), 16);
// 				x++;
// 			}
// 			y++;
// 		}
// }


// void draw_vertical_line(t_cub *cub, int x, int y1, int y2, int color)
// {
// 	double			y_count;
// 	static double	x_count;
// 	double			tx_step;
	
// 	tx_step = (double)cub->tx_data[1]->height / cub->ray->wallLineHeight;
// 	if (cub->ray->wallLineHeight < 0)
// 		tx_step = (double)cub->tx_data[1]->height / cub->ray->wallLineHeight * -1;

// 	y_count = 0;
// 	while (y1 != y2)
// 	{
// 		if (y_count < cub->tx_data[1]->width && y_count < cub->tx_data[1]->height)
// 		{
// 			pixel_put(cub, x, y1, cub->tx_data[1]->texture[(int)y_count][(int)x_count]);
// 			if (y_count + tx_step < cub->tx_data[1]->height)
// 				y_count += tx_step;
// 		}
// 		else
// 			pixel_put(cub, x, y1, 0xfffffff);
// 		if (y1 > y2)
// 			y1--;
// 		else
// 			y1++;
// 	}
// 	if (cub->ray->hitSide == _Y_ && cub->ray->rayDir[_Y_] < 0)
// 		x_count += tx_step;
// 	else
// 		x_count = 0;
// }
