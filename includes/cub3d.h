/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-s <jlucas-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 19:42:56 by jlucas-s          #+#    #+#             */
/*   Updated: 2023/08/06 21:14:05 by jlucas-s         ###   ########.fr       */
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

# define COLISION_DIS	0.5
# define MOVE_SPEED		0.1
# define ROTATE_SPEED	0.1

# define PI			3.141592653589793
# define _X_		0
# define _Y_		1

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

typedef struct s_raycasting
{
	double	multiplier;
	double	cameraPixel[2];
	double	rayDir[2];
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

typedef struct s_player
{
	double	dir[2]; 
    double	plane[2];
	double 	pos[2];

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

typedef struct s_img
{
	void    *ptr;
	int		*data;
	int		largura;
	int		altura;
	int     size_l;
	int     bpp;
	int     endian;
    int     **texture;

}				t_img;

typedef struct s_cub
{
	t_map			*map;
	t_mlx			*mlx;
	t_player		*player;
	t_raycasting	*ray;
	t_img			*img[4];
	
}	t_cub;

//	FUNCTIONS	//
// Init
void	init_map(t_cub *cub, char *file);
void	init_mlx(t_cub *cub);
void	init_img(t_cub *cub);
int		line_is_empty(char *str);
// Get
int		get_textures(t_cub *cub, char **content);
void	get_map(t_cub *cub, char **content, int i_map);
// Validation
void	map_validation(t_cub *cub);


// Draw
void	draw(t_cub *cub);
void	draw_map(t_cub *cub);
void	draw_square(t_cub *cub, int x, int y, int size);
void	floor_and_ceiling(t_cub *cub);

// Hooks
void    rotate(double *x, double *y, double angle);
void	hook_handler(t_cub *cub);

// Allocs
void	exit_cub(t_cub *cub, int i);
void	init_player(t_cub *cub);

#endif