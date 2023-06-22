/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-s <jlucas-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 19:42:56 by jlucas-s          #+#    #+#             */
/*   Updated: 2023/06/21 20:35:00 by jlucas-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

//  INCLUDES  //
# include "../lib/include/libft.h"
# include <stdio.h>
# include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

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

typedef struct s_cub
{

	t_map	*map;

}	t_cub;


//  FUNCTIONS  //
// init //
t_cub	*init_cub(char *file);


#endif