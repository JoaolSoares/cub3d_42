/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dofranci <dofranci@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 19:42:56 by jlucas-s          #+#    #+#             */
/*   Updated: 2023/08/16 18:25:42 by dofranci         ###   ########.fr       */
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
# define WIN_WIDTH		800
# define WIN_HEIGHT		600

# define ESC_KEY		65307
# define W_KEY			119
# define A_KEY			97
# define S_KEY			115
# define D_KEY			100
# define LEFT_KEY		65361
# define RIGHT_KEY		65363

# define COLISION_DIS	0.5
# define MOVE_SPEED		0.1
# define ROTATE_SPEED	0.1

# define PI				3.141592653589793
# define _X_			0
# define _Y_			1

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

typedef struct s_map
{
	char	**map;
	int		height;
	int		width;
	char	**textures_paths;
	int		floor_color;
	int		ceil_color;
	int		player_x;
	int		player_y;

}	t_map;

typedef struct s_raycasting
{
	double	multiplier;
	double	camera_pixel[2];
	double	ray_dir[2];
	double	delta_dist[2];
	double	map_pos[2];
	double	dist_to_side[2];
	double	step[2];
	int		hit;
	int		hit_side;
	double	dda_line_size[2];
	double	wall_map_pos[2];
	double	perpendicular_dist;
	double	wall_line_height;
	double	line_start;
	double	line_end;

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

typedef struct s_texture
{
	void    *ptr;
	int		*data;
	int		width;
	int		height;
	int     size_l;
	int     bpp;
	int     endian;
    int     **texture;

}	t_texture;

typedef struct s_cub
{
	t_map			*map;
	t_mlx			*mlx;
	t_player		*player;
	t_raycasting	*ray;
	t_texture		*tx_data[4];
	
}	t_cub;

//	FUNCTIONS	//
// Init
void	read_file(t_cub *cub, char *file);
void	init_mlx(t_cub *cub);
void	init_textures(t_cub *cub);
int		line_is_empty(char *str);
// Get
void	get_textures_path(t_cub *cub, char **content, int *file_index);
void	get_map(t_cub *cub, char **content, int file_index);
// Validation
void	map_validation(t_cub *cub);

// Draw
void	draw(t_cub *cub);
void	draw_vertical_line(t_cub *cub, int x, int y1, int y2);
void	raycasting(t_cub *cub);

// Hooks
void    rotate(double *x, double *y, double angle);
void	move_vertical(int keycode, t_cub *cub, double *strafedir);
void	move_horizontal(int keycode, t_cub *cub, double *strafedir);
void	hook_handler(t_cub *cub);

// Allocs
void	free_map(t_cub *cub, int exit_num);
void	free_textures(t_cub *cub);
void	free_mlx(t_cub *cub);
void	exit_cub(t_cub *cub, int exit_num);

void	init_player(t_cub *cub);

#endif