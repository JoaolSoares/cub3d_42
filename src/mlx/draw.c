/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-s <jlucas-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 19:44:21 by jlucas-s          #+#    #+#             */
/*   Updated: 2023/08/03 18:32:52 by jlucas-s         ###   ########.fr       */
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
		while(x++ < 800)
		{
			y = 0;
			while(y++ < 300)
				pixel_put(cub, x, y, cub->map->ceil_color);
		}
		x = 0;
		while(x++ < 800)
		{
			y = 300;
			while(y++ < 600)
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

# define _X_ 0
# define _Y_ 1

void draw_vertical_line(t_cub *cub, int x, int y1, int y2, int color)
{
	while (y1 >= y2)
	{
		pixel_put(cub, x, y1, color);
		y1--;
	}
}

void draw(t_cub *cub)
{
	double	pixel;
	double	multiplier;
	double	cameraPixel[2];
	double	rayDir[2];
	double	mag;
	double	deltaDist[2];
	double	mapPos[2];
	double	distToSide[2];
	double	step[2];
	int		hit;
	int		hitSide;
	double	ddaLineSize[2];
	double	wallMapPos[2];
	double	perpendicularDist;
	double	wallLineHeight;
	double	lineStartY;
	double	lineEndY;

	floor_and_ceiling(cub);
	pixel = 0;
	while (pixel < WIN_WIDTH)
	{
		multiplier			= 2 * (pixel / WIN_WIDTH) - 1;
		
		cameraPixel[_X_]	= cub->player->planeX * multiplier;
		cameraPixel[_Y_]	= cub->player->planeY * multiplier;
	
		
		rayDir[_X_]			= cub->player->dirX + cameraPixel[_X_];
		rayDir[_Y_]			= cub->player->dirY + cameraPixel[_Y_];

		// mag					= sqrt(pow(rayDir[_X_], 2) + pow(rayDir[_Y_], 2));
		// deltaDist[_X_]		= abs(1 / rayDir[_X_]);
		// deltaDist[_Y_]		= abs(1 / rayDir[_Y_]);
		if (rayDir[_X_] == 0)
		{
			deltaDist[_X_]	= 1;
			deltaDist[_Y_]	= 0;
		}
		else
		{
			if (rayDir[_Y_] != 0)
				deltaDist[_X_]	= fabs(1 / rayDir[_X_]);
		}
		
		if (rayDir[_Y_] == 0)
		{
			deltaDist[_Y_]	= 1;
			deltaDist[_X_]	= 0;
		}
		else
		{
			if (rayDir[_X_] != 0)
				deltaDist[_Y_]	= fabs(1 / rayDir[_Y_]); 
		}


		mapPos[_X_]			= floor(cub->player->posx);
		mapPos[_Y_]			= floor(cub->player->posy);


		if (rayDir[_X_] < 0)
		{
			distToSide[_X_]		= (cub->player->posx - mapPos[_X_]) * deltaDist[_X_];
			step[_X_]			= -1;
		}
		else
		{
			distToSide[_X_]		= (mapPos[_X_] + 1 - cub->player->posx) * deltaDist[_X_];
			step[_X_]			= 1;
		}

		if (rayDir[_Y_] < 0)
		{
			distToSide[_Y_]	= (cub->player->posy - mapPos[_Y_]) * deltaDist[_Y_];
			step[_Y_]			= -1;
		}
		else
		{
			distToSide[_Y_]		= (mapPos[_Y_] + 1 - cub->player->posy) * deltaDist[_Y_];
			step[_Y_]			= 1;
		}
	

		ddaLineSize[_X_]	= distToSide[_X_];
		ddaLineSize[_Y_]	= distToSide[_Y_];

		wallMapPos[_X_]		= mapPos[_X_];		
		wallMapPos[_Y_]		= mapPos[_Y_];
		
		hit					= FALSE;
		while (hit == FALSE)
		{
			if (ddaLineSize[_X_] < ddaLineSize[_Y_])
			{
				wallMapPos[_X_]		+= step[_X_];
				ddaLineSize[_X_]	+= deltaDist[_X_];
				hitSide				= _X_;
			}
			else
			{
				wallMapPos[_Y_]		+= step[_Y_];
				ddaLineSize[_Y_]	+= deltaDist[_Y_];
				hitSide				= _Y_;
			}
			if (cub->map->map[(int)wallMapPos[_X_]][(int)wallMapPos[_Y_]] == '1')
				hit					= TRUE;
		}

		if (hitSide == _X_)
		{
			perpendicularDist = fabs(wallMapPos[_X_] - cub->player->posx + ((1 - (int)step[_X_] / 2))) / rayDir[_X_];
		}
		else
		{
			perpendicularDist = fabs(wallMapPos[_Y_] - cub->player->posy + ((1 - (int)step[_Y_] / 2))) / rayDir[_Y_];
		}

		wallLineHeight	= WIN_HEIGHT / perpendicularDist;
		lineStartY		= WIN_HEIGHT / 2 - wallLineHeight / 2;
		lineEndY		= WIN_HEIGHT / 2 + wallLineHeight / 2;

		int color = hitSide ? 0xFF0000 : 0x8b0000;
		

		draw_vertical_line(cub, pixel, (int)lineStartY, (int)lineEndY, color);

		pixel++;
	}




	
	mlx_put_image_to_window(cub->mlx->mlx, cub->mlx->win, cub->mlx->img, 0, 0);
	mlx_destroy_image(cub->mlx->mlx, cub->mlx->img);






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
		

}
