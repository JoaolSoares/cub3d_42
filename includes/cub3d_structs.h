/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_structs.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-s <jlucas-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 21:23:44 by jlucas-s          #+#    #+#             */
/*   Updated: 2023/08/17 21:32:10 by jlucas-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//  DEFINES  //
#define WIN_WIDTH 		800
#define WIN_HEIGHT		600

#define ESC_KEY			65307
#define W_KEY			119
#define A_KEY			97
#define S_KEY			115
#define D_KEY			100
#define LEFT_KEY		65361
#define RIGHT_KEY		65363

#define COLISION_DIS	0.5
#define MOVE_SPEED		0.1
#define ROTATE_SPEED	0.1

#define PI				3.141592653589793
#define _X_				0
#define _Y_				1

//  STRUCTS  //
typedef enum e_tx
{
	NO,
	SO,
	WE,
	EA,
}	t_tx;

typedef enum e_bool
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
	int		tex[2];
	int		tex_side;
	double	wall_x;

}	t_raycasting;

typedef struct s_player
{
	double	dir[2]; 
	double	plane[2];
	double	pos[2];

}	t_player;

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
	void	*ptr;
	int		*data;
	int		width;
	int		height;
	int		size_l;
	int		bpp;
	int		endian;
	int		**texture;

}	t_texture;

typedef struct s_cub
{
	t_map			*map;
	t_mlx			*mlx;
	t_player		*player;
	t_raycasting	*ray;
	t_texture		*tx_data[4];

}	t_cub;