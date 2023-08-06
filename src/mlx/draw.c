/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-s <jlucas-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 19:44:21 by jlucas-s          #+#    #+#             */
/*   Updated: 2023/08/06 17:14:51 by jlucas-s         ###   ########.fr       */
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

void floor_and_ceiling(t_cub *cub)
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

void draw_square(t_cub *cub, int x, int y, int size)
{
		int tempy;
		int tempx;
		int color; 

		color = 0xFFFFFF;
		if(size != 16)
			color = 0x008000;
		tempy = y;
		tempx = x;
		while(x++ < (tempx + size))
		{
			y = tempy;
			while(y++ < (tempy + size))
				pixel_put(cub, x, y, color);
		}
}

void draw_map(t_cub *cub)
{
		int x;
		int y;
		
		x = 0;
		y = 0;
		while(cub->map->map[y])
		{
			x = 0;
			while(cub->map->map[y][x])
			{
				if(cub->map->map[y][x] == '1')
					draw_square(cub, (x * 16), (y * 16), 16);
				x++;
			}
			y++;
		}
}

void draw_vertical_line(t_cub *cub, int x, int y1, int y2, int color)
{
	while (y1 != y2)
	{
		pixel_put(cub, x, y1, color);
		if (y1 > y2)
			y1--;
		else
			y1++;
	}
}

void draw(t_cub *cub)
{
	double			pixel;

	cub->mlx->img = mlx_new_image(cub->mlx->mlx, WIN_WIDTH, WIN_HEIGHT);
    cub->mlx->addr = mlx_get_data_addr(cub->mlx->img, &cub->mlx->bits_per_pixel, &cub->mlx->line_length, &cub->mlx->endian);

	floor_and_ceiling(cub);
	pixel = 0;
	while (pixel <= WIN_WIDTH)
	{
		cub->ray->multiplier			= 2 * (pixel / WIN_WIDTH) - 1;
		
		cub->ray->cameraPixel[_X_]	= cub->player->plane[_X_] * cub->ray->multiplier;
		cub->ray->cameraPixel[_Y_]	= cub->player->plane[_Y_] * cub->ray->multiplier;
		
		cub->ray->rayDir[_X_]		= cub->player->dir[_X_] + cub->ray->cameraPixel[_X_];
		cub->ray->rayDir[_Y_]		= cub->player->dir[_Y_] + cub->ray->cameraPixel[_Y_];


		if (cub->ray->rayDir[_X_] == 0)
		{
			cub->ray->deltaDist[_X_]	= 1;
			cub->ray->deltaDist[_Y_]	= 0;
		}
		else
		{
			if (cub->ray->rayDir[_Y_] != 0)
				cub->ray->deltaDist[_X_]	= fabs(1 / cub->ray->rayDir[_X_]);
		}
		
		if (cub->ray->rayDir[_Y_] == 0)
		{
			cub->ray->deltaDist[_Y_]	= 1;
			cub->ray->deltaDist[_X_]	= 0;
		}
		else
		{
			if (cub->ray->rayDir[_X_] != 0)
				cub->ray->deltaDist[_Y_]	= fabs(1 / cub->ray->rayDir[_Y_]); 
		}


		cub->ray->mapPos[_X_]			= floor(cub->player->pos[_X_]);
		cub->ray->mapPos[_Y_]			= floor(cub->player->pos[_Y_]);


		if (cub->ray->rayDir[_X_] < 0)
		{
			cub->ray->distToSide[_X_]	= (cub->player->pos[_X_] - cub->ray->mapPos[_X_]) * cub->ray->deltaDist[_X_];
			cub->ray->step[_X_]			= -1;
		}
		else
		{
			cub->ray->distToSide[_X_]	= (cub->ray->mapPos[_X_] + 1 - cub->player->pos[_X_]) * cub->ray->deltaDist[_X_];
			cub->ray->step[_X_]			= 1;
		}

		if (cub->ray->rayDir[_Y_] < 0)
		{
			cub->ray->distToSide[_Y_]	= (cub->player->pos[_Y_] - cub->ray->mapPos[_Y_]) * cub->ray->deltaDist[_Y_];
			cub->ray->step[_Y_]			= -1;
		}
		else
		{
			cub->ray->distToSide[_Y_]	= (cub->ray->mapPos[_Y_] + 1 - cub->player->pos[_Y_]) * cub->ray->deltaDist[_Y_];
			cub->ray->step[_Y_]			= 1;
		}
	

		cub->ray->ddaLineSize[_X_]	= cub->ray->distToSide[_X_];
		cub->ray->ddaLineSize[_Y_]	= cub->ray->distToSide[_Y_];

		cub->ray->wallMapPos[_X_]	= cub->ray->mapPos[_X_];		
		cub->ray->wallMapPos[_Y_]	= cub->ray->mapPos[_Y_];
		
		cub->ray->hit				= FALSE;
		while (cub->ray->hit == FALSE)
		{
			if (cub->ray->ddaLineSize[_X_] < cub->ray->ddaLineSize[_Y_])
			{
				cub->ray->wallMapPos[_X_]		+= cub->ray->step[_X_];
				cub->ray->ddaLineSize[_X_]		+= cub->ray->deltaDist[_X_];
				cub->ray->hitSide				= _X_;
			}
			else
			{
				cub->ray->wallMapPos[_Y_]		+= cub->ray->step[_Y_];
				cub->ray->ddaLineSize[_Y_]		+= cub->ray->deltaDist[_Y_];
				cub->ray->hitSide				= _Y_;
			}
			if (cub->map->map[(int)cub->ray->wallMapPos[_X_]][(int)cub->ray->wallMapPos[_Y_]] == '1')
				cub->ray->hit					= TRUE;
		}

		if (cub->ray->hitSide == _X_)
			cub->ray->perpendicularDist = fabs(cub->ray->wallMapPos[_X_] - cub->player->pos[_X_] + ((1 - cub->ray->step[_X_]) / 2)) / cub->ray->rayDir[_X_];
		else
			cub->ray->perpendicularDist = fabs(cub->ray->wallMapPos[_Y_] - cub->player->pos[_Y_] + ((1 - cub->ray->step[_Y_]) / 2)) / cub->ray->rayDir[_Y_];

		cub->ray->wallLineHeight	= WIN_HEIGHT / cub->ray->perpendicularDist;
		cub->ray->lineStartY		= WIN_HEIGHT / 2 - cub->ray->wallLineHeight / 2;
		cub->ray->lineEndY			= WIN_HEIGHT / 2 + cub->ray->wallLineHeight / 2;

		int color = cub->ray->hitSide == _Y_ ? 0xFF0000 : 0x8b0000;

		draw_vertical_line(cub, WIN_WIDTH - pixel, (int)cub->ray->lineStartY, (int)cub->ray->lineEndY, color);

		pixel++;
	}

	mlx_put_image_to_window(cub->mlx->mlx, cub->mlx->win, cub->mlx->img, 0, 0);
	mlx_destroy_image(cub->mlx->mlx, cub->mlx->img);
}




	// draw_map(cub);
	// draw_square(cub, cub->player->posx, cub->player->posy, 8); // player

	// int x;
	// while(1)
	// {      
	//   x = -1;
	//   while(++x < WIN_WIDTH)
	//   {
	//     cub->player->cameraX = 2 * (x / (double)WIN_WIDTH - 1);
	//     cub->player->rayDirX = cub->player->dirX + cub->player->planeX * cub->player->cameraX;
	//     cub->player->rayDirY = cub->player->dirY + cub->player->planeY * cub->player->cameraX;
			
	//     cub->player->deltaDistX = sqrt(1 + (cub->player->rayDirY * cub->player->rayDirY) / (cub->player->rayDirX * cub->player->rayDirX));
	//     cub->player->deltaDistY = sqrt(1 + (cub->player->rayDirX * cub->player->rayDirX) / (cub->player->rayDirY * cub->player->rayDirY));
	//     int playerPos[1];
	//     playerPos[0] = floor();
	//   }
	// }
		