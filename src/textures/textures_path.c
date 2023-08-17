/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-s <jlucas-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 23:06:19 by jlucas-s          #+#    #+#             */
/*   Updated: 2023/08/16 19:36:56 by jlucas-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	rgb_to_hex(char *rgb)
{
	int		hex;
	char	**split_rgb;
	int		int_rgb[3];

	split_rgb = ft_split(rgb, ',', 0);
	int_rgb[0] = ft_atoi(split_rgb[0]);
	int_rgb[1] = ft_atoi(split_rgb[1]);
	int_rgb[2] = ft_atoi(split_rgb[2]);
	ft_freemtx(split_rgb);
	hex = (int_rgb[0] << 16) | (int_rgb[1] << 8) | (int_rgb[2]);
	return (hex);
}

static void	texture_error(t_cub *cub, char **content, char **temp)
{
	int	i;

	ft_putstr_fd("Error\nIncorrectly defined textures\n", STDERR_FILENO);
	ft_freemtx(temp);
	ft_freemtx(content);
	i = -1;
	while (++i < 4)
		free(cub->map->textures_paths[i]);
	free(cub->map->textures_paths);
	free(cub->map);
	free(cub);
	exit(41);
}

static int	texture_assign(t_cub *cub, char **temp)
{
	if (!ft_strncmp(temp[0], "NO", 3) && cub->map->textures_paths[NO] == 0)
		cub->map->textures_paths[NO] = \
		ft_strdup_until(temp[1], ft_strlen(temp[1]) - 1);
	else if (!ft_strncmp(temp[0], "SO", 3) && cub->map->textures_paths[SO] == 0)
		cub->map->textures_paths[SO] = \
		ft_strdup_until(temp[1], ft_strlen(temp[1]) - 1);
	else if (!ft_strncmp(temp[0], "WE", 3) && cub->map->textures_paths[WE] == 0)
		cub->map->textures_paths[WE] = \
		ft_strdup_until(temp[1], ft_strlen(temp[1]) - 1);
	else if (!ft_strncmp(temp[0], "EA", 3) && cub->map->textures_paths[EA] == 0)
		cub->map->textures_paths[EA] = \
		ft_strdup_until(temp[1], ft_strlen(temp[1]) - 1);
	else if (!ft_strncmp(temp[0], "F", 2) && cub->map->floor_color == 0)
		cub->map->floor_color = rgb_to_hex(temp[1]);
	else if (!ft_strncmp(temp[0], "C", 2) && cub->map->ceil_color == 0)
		cub->map->ceil_color = rgb_to_hex(temp[1]);
	else
		return (FALSE);
	return (TRUE);
}

void	get_textures_path(t_cub *cub, char **content, int *file_index)
{
	int			texture_posi;
	char		**temp;

	*file_index = 0;
	texture_posi = 0;
	while (content[*file_index])
	{
		if (texture_posi <= 5 && line_is_empty(content[*file_index]) == FALSE)
		{
			temp = ft_split(content[*file_index], ' ', 0);
			if (texture_assign(cub, temp) == TRUE)
			{
				texture_posi++;
				ft_freemtx(temp);
			}
			else
				texture_error(cub, content, temp);
		}
		else if (texture_posi > 5)
			return ;
		*file_index += 1;
	}
}
