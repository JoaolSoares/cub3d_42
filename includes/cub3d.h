/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-s <jlucas-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 19:42:56 by jlucas-s          #+#    #+#             */
/*   Updated: 2023/07/27 20:34:36 by jlucas-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

//  INCLUDES  //
# include "../lib/include/libft.h"
# include <stdio.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <mlx.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include <math.h>

//  DEFINES  //
//	Window
# define WIN_WIDTH	800
# define WIN_HEIGHT 600
//	Keys
# define ESC_KEY	65307
# define W_KEY		119
# define A_KEY		97
# define S_KEY		115
# define D_KEY		100
# define LEFT_KEY	65361
# define RIGHT_KEY	65363
# define PI			3.141592653589793

//  STRUCTS  //
typedef enum s_tx
{
	NO,
	SO,
	WE,
	EA,

}	t_tx;

typedef enum s_bool
{
	FALSE,
	TRUE,

}	t_bool;

typedef struct s_linepoint
{
	int x;
	int y;
	int xo;
	int yo;

}	t_linepoint;

typedef struct s_map
{
	char	**map;
	int		height;
	int		width;
	char	**textures;
	int		floor_color;
	int		ceil_color;
	int		player_x;
	int		player_y;

}	t_map;

typedef struct s_player
{
	double	dirX; 
	double	dirY;
    double	planeX;
	double	planeY;
    double	time;
    double	oldTime;
	double	cameraX;
	double	rayDirX;
	double	rayDirY;
	double	deltaDistX;
	double	deltaDistY;
	double 	posx;
    double	posy;
	double	deltaPosX;
	double	deltaPosY;
	double	deltaPosA;
	
} t_player; 

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;

}	t_mlx;

typedef struct s_cub
{
	t_map		*map;
	t_mlx		*mlx;
	t_player	*player;
}	t_cub;


//	FUNCTIONS	//
//-------------- MAP --------------//
// Init
void	init_map(t_cub *cub, char *file);
void	init_mlx(t_cub *cub);
int		line_is_empty(char *str);

// Get
int		get_textures(t_cub *cub, char **content);
void	get_map(t_cub *cub, char **content, int i_map);

// Validation
void	map_validation(t_cub *cub);

//-------------- MLX --------------//
// Draw
void	draw(t_cub *cub);
void	draw_map(t_cub *cub);
void	draw_square(t_cub *cub, int x, int y, int size);
void	floor_and_ceiling(t_cub *cub);

// Hooks
void	hook_handler(t_cub *cub);

// Free
void	exit_cub(t_cub *cub, int i);

#endif