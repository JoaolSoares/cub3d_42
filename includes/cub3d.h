/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dofranci <dofranci@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 19:42:56 by jlucas-s          #+#    #+#             */
/*   Updated: 2023/07/04 21:04:58 by dofranci         ###   ########.fr       */
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
# include <math.h>
# include <X11/keysym.h>
# include <X11/X.h>

//  DEFINES  //


//  STRUCTS  //
typedef enum s_tx
{
	NO,
	SO,
	WE,
	EA,
	F,
	C,

}	t_tx;

typedef enum s_bool
{
	FALSE,
	TRUE,

}	t_bool;

typedef struct s_map
{
	char		**map;
	int			height;
	int			width;
	char		**textures;
}	t_map;

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

	t_map	*map;
	t_mlx	*mlx;

}	t_cub;


//  FUNCTIONS  //
// init //
void	init_map(t_cub *cub, char *file);
void	init_mlx(t_cub *cub);

// map //
int		get_textures(t_cub *cub, char **content);
void	get_map(t_cub *cub, char **content, int i_map);

// utils //
int		line_is_empty(char *str);

// validation //
void	map_validation(t_cub *cub);

// draw //
void draw(t_cub *cub);

// free //
void	exit_cub(t_cub *cub, int i);

#endif