/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dofranci <dofranci@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 19:44:21 by jlucas-s          #+#    #+#             */
/*   Updated: 2023/07/25 10:39:31 by dofranci         ###   ########.fr       */
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

// static void floor_and_ceiling(t_cub *cub)
// {
//     int x;
//     int y;

//     x = 0;
//     while(x++ < 800)
//     {
//       y = 0;
//       while(y++ < 300)
//         pixel_put(cub, x, y, cub->map->ceil_color);
//     }
//     x = 0;
//     while(x++ < 800)
//     {
//       y = 300;
//       while(y++ < 600)
//         pixel_put(cub, x, y, cub->map->floor_color);
//     }
// }

// static void set_data(t_map *map)
// { 
//   map->dirX = -1;
//   map->dirY = 0; 
//   map->planeX = 0; 
//   map->planeY = 0.66; 
//   map->time = 0; 
//   map->oldTime = 0; 
// }

void draw_player(t_cub *cub, int posx, int posy)
{
    int x;
    int y;

    x = posx;
    while(x++ < (posx + 10))
    {
      y = posy;
      while(y++ < (posy + 10))
      {
        pixel_put(cub, x, y, 0x008000);
      }
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

void draw_map(t_cub *cub, int opt)
{
    t_linepoint *line;

    line = malloc(sizeof (t_linepoint));
    line->y = 0;
    line->x = 0;
    line->yo = 0;
    line->xo = 0;
    while(cub->map->map[line->y])
    {
      line->x = 0;
      while(cub->map->map[line->y][line->x])
      {
        if(cub->map->map[line->y][line->x] == '1')
        {
          draw_square(cub, (line->x * 16), (line->y * 16), 16);
        }
        else if(cub->map->map[line->y][line->x] != '1' && cub->map->map[line->y][line->x] != '0' && cub->map->map[line->y][line->x] != ' ' && opt == 0)
        {
              cub->posx = (line->x * 16);
              cub->posy = (line->y * 16);
              draw_square(cub, cub->posx, cub->posy, 10);
        }
        line->x++;
      }
      line->y++;
    }
    free(line);
}

void draw(t_cub *cub)
{
    cub->mlx->img = mlx_new_image(cub->mlx->mlx, WIN_WIDTH, WIN_HEIGHT);
    cub->mlx->addr = mlx_get_data_addr(cub->mlx->img, &cub->mlx->bits_per_pixel, &cub->mlx->line_length, &cub->mlx->endian);
    draw_map(cub, 0);
    mlx_put_image_to_window(cub->mlx->mlx, cub->mlx->win, cub->mlx->img, 0, 0);
    mlx_destroy_image(cub->mlx->mlx, cub->mlx->img);
    // draw_player(cub, cub->posx, cub->posy);
    // draw_player(cub, cub->posx, cub->posy);
    
    // draw_map(cub);
    //floor_and_ceiling(cub);
    // set_data(cub->map);
    // while(1)
    // {      
    //   x = 0;
    //   while(x++ < WIN_WIDTH)
    //   {
    //     cub->map->cameraX = 2 * (x / (double)WIN_WIDTH - 1);
    //     cub->map->rayDirX = cub->map->dirX + cub->map->planeX * cub->map->cameraX;
    //     cub->map->rayDirY = cub->map->dirY + cub->map->planeY * cub->map->cameraX;
        
    //     cub->map->deltaDistX = sqrt(1 + (cub->map->rayDirY * cub->map->rayDirY) / (cub->map->rayDirX * cub->map->rayDirX));
    //     cub->map->deltaDistY = sqrt(1 + (cub->map->rayDirX * cub->map->rayDirX) / (cub->map->rayDirY * cub->map->rayDirY));
    //     int mapPos[1];
    //     mapPos[0] = floor();
    //   }
    // }
    

}
