/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dofranci <dofranci@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 19:44:21 by jlucas-s          #+#    #+#             */
/*   Updated: 2023/07/25 17:00:51 by dofranci         ###   ########.fr       */
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

void draw(t_cub *cub)
{
   // floor_and_ceiling(cub);
    draw_map(cub);
    draw_square(cub, cub->player->posx, cub->player->posy, 8); // player
    mlx_put_image_to_window(cub->mlx->mlx, cub->mlx->win, cub->mlx->img, 0, 0);
    mlx_destroy_image(cub->mlx->mlx, cub->mlx->img);

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
