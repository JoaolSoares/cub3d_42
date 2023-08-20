/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-s <jlucas-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 19:42:56 by jlucas-s          #+#    #+#             */
/*   Updated: 2023/08/17 21:24:54 by jlucas-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

//  INCLUDES  //
# include "../lib/include/libft.h"
# include "cub3d_structs.h"
# include <stdio.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <mlx.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include <math.h>

//	FUNCTIONS	//
void	read_file(t_cub *cub, char *file);
int		line_is_empty(char *str);

// Textures
void	get_textures_path(t_cub *cub, char **content, int *file_index);
void	init_textures(t_cub *cub);

// Map
void	map_validation(t_cub *cub);
void	get_map(t_cub *cub, char **content, int file_index);
// Player
void	init_player(t_cub *cub);

// Draw
void	pixel_put(t_cub *cub, int x, int y, int color);
void	draw(t_cub *cub);
void	draw_vertical_line(t_cub *cub, int x);
void	raycasting(t_cub *cub);

// Mlx
void	init_mlx(t_cub *cub);
void	rotate(double *x, double *y, double angle);
void	move_vertical(int keycode, t_cub *cub);
void	move_horizontal(int keycode, t_cub *cub, double *strafedir);
void	hook_handler(t_cub *cub);

// Allocs
void	free_map(t_cub *cub, int exit_num);
void	free_textures(t_cub *cub);
void	free_mlx(t_cub *cub);
void	exit_cub(t_cub *cub, int exit_num);

#endif