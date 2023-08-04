/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-s <jlucas-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 19:44:21 by jlucas-s          #+#    #+#             */
/*   Updated: 2023/08/04 16:42:43 by jlucas-s         ###   ########.fr       */
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
typedef struct s_raycasting
{
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

}	t_raycasting;

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
	double			pixel;
	t_raycasting	*ray;

	ray = malloc(sizeof(t_raycasting));

	floor_and_ceiling(cub);
	pixel = 0;
	while (pixel < WIN_WIDTH)
	{
		ray->multiplier			= 2 * (pixel / WIN_WIDTH) - 1;
		
		ray->cameraPixel[_X_]	= cub->player->planeX * ray->multiplier;
		ray->cameraPixel[_Y_]	= cub->player->planeY * ray->multiplier;
	
		
		ray->rayDir[_X_]		= cub->player->dirX + ray->cameraPixel[_X_];
		ray->rayDir[_Y_]		= cub->player->dirY + ray->cameraPixel[_Y_];

		// mag					= sqrt(pow(rayDir[_X_], 2) + pow(rayDir[_Y_], 2));
		// deltaDist[_X_]		= abs(1 / rayDir[_X_]);
		// deltaDist[_Y_]		= abs(1 / rayDir[_Y_]);
		if (ray->rayDir[_X_] == 0)
		{
			ray->deltaDist[_X_]	= 1;
			ray->deltaDist[_Y_]	= 0;
		}
		else
		{
			if (ray->rayDir[_Y_] != 0)
				ray->deltaDist[_X_]	= fabs(1 / ray->rayDir[_X_]);
		}
		
		if (ray->rayDir[_Y_] == 0)
		{
			ray->deltaDist[_Y_]	= 1;
			ray->deltaDist[_X_]	= 0;
		}
		else
		{
			if (ray->rayDir[_X_] != 0)
				ray->deltaDist[_Y_]	= fabs(1 / ray->rayDir[_Y_]); 
		}


		ray->mapPos[_X_]			= floor(cub->player->posx);
		ray->mapPos[_Y_]			= floor(cub->player->posy);


		if (ray->rayDir[_X_] < 0)
		{
			ray->distToSide[_X_]	= (cub->player->posx - ray->mapPos[_X_]) * ray->deltaDist[_X_];
			ray->step[_X_]			= -1;
		}
		else
		{
			ray->distToSide[_X_]	= (ray->mapPos[_X_] + 1 - cub->player->posx) * ray->deltaDist[_X_];
			ray->step[_X_]			= 1;
		}

		if (ray->rayDir[_Y_] < 0)
		{
			ray->distToSide[_Y_]	= (cub->player->posy - ray->mapPos[_Y_]) * ray->deltaDist[_Y_];
			ray->step[_Y_]			= -1;
		}
		else
		{
			ray->distToSide[_Y_]	= (ray->mapPos[_Y_] + 1 - cub->player->posy) * ray->deltaDist[_Y_];
			ray->step[_Y_]			= 1;
		}
	

		ray->ddaLineSize[_X_]	= ray->distToSide[_X_];
		ray->ddaLineSize[_Y_]	= ray->distToSide[_Y_];

		ray->wallMapPos[_X_]	= ray->mapPos[_X_];		
		ray->wallMapPos[_Y_]	= ray->mapPos[_Y_];
		
		ray->hit				= FALSE;
		while (ray->hit == FALSE)
		{
			if (ray->ddaLineSize[_X_] < ray->ddaLineSize[_Y_])
			{
				ray->wallMapPos[_X_]		+= ray->step[_X_];
				ray->ddaLineSize[_X_]	+= ray->deltaDist[_X_];
				ray->hitSide				= _X_;
			}
			else
			{
				ray->wallMapPos[_Y_]		+= ray->step[_Y_];
				ray->ddaLineSize[_Y_]	+= ray->deltaDist[_Y_];
				ray->hitSide				= _Y_;
			}
			if (cub->map->map[(int)ray->wallMapPos[_X_]][(int)ray->wallMapPos[_Y_]] == '1')
				ray->hit					= TRUE;
		}

		if (ray->hitSide == _X_)
		{
			ray->perpendicularDist = fabs(ray->wallMapPos[_X_] - cub->player->posx + ((1 - (int)ray->step[_X_] / 2))) / ray->rayDir[_X_];
		}
		else
		{
			ray->perpendicularDist = fabs(ray->wallMapPos[_Y_] - cub->player->posy + ((1 - (int)ray->step[_Y_] / 2))) / ray->rayDir[_Y_];
		}

		ray->wallLineHeight	= WIN_HEIGHT / ray->perpendicularDist;
		ray->lineStartY		= WIN_HEIGHT / 2 - ray->wallLineHeight / 2;
		ray->lineEndY		= WIN_HEIGHT / 2 + ray->wallLineHeight / 2;

		int color = ray->hitSide == _Y_ ? 0xFF0000 : 0x8b0000;
		

		draw_vertical_line(cub, pixel, (int)ray->lineStartY, (int)ray->lineEndY, color);

		pixel++;
	}


	mlx_put_image_to_window(cub->mlx->mlx, cub->mlx->win, cub->mlx->img, 0, 0);
	mlx_destroy_image(cub->mlx->mlx, cub->mlx->img);
	free(ray);
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
		