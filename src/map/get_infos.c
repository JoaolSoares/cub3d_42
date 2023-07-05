/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_infos.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-s <jlucas-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 21:28:53 by jlucas-s          #+#    #+#             */
/*   Updated: 2023/07/04 22:14:59 by jlucas-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int line_is_empty(char *str)
{
	int i;

	i = 0;
	while(str && str[i] && str[i] != '\n')
	{
		if(str[i] != ' ' && str[i] != '\t')
			return (FALSE);	
		i++;
	}
	return (TRUE);
}

static int rgb_to_hex(char *rgb) 
{
    int     hex;
    char    **split_rgb;
    int     int_rgb[3];

    split_rgb = ft_split(rgb, ',', 0);

    int_rgb[0] = ft_atoi(split_rgb[0]);
    int_rgb[1] = ft_atoi(split_rgb[1]);
    int_rgb[2] = ft_atoi(split_rgb[2]);
    ft_freemtx(split_rgb);

	// JULGAR NECESSIDADE DISSO (não quebra o codigo)
    // if (int_rgb[0] < 0 || int_rgb[0] > 255 || 
    //     int_rgb[1] < 0 || int_rgb[1] > 255 || 
    //     int_rgb[2] < 0 || int_rgb[2] > 255)
    // {
    //     return (-1);
    // }
    hex = (int_rgb[0] << 16) | (int_rgb[1] << 8) | (int_rgb[2]);
    return (hex);
}

int	get_textures(t_cub *cub, char **content)
{
	int			i;
	int			texture_posi;
	char		**temp;

	i = 0;
	texture_posi = 0;
	while (content[i])
	{
		if (texture_posi <= 5 && line_is_empty(content[i]) == FALSE)
		{
			temp = ft_split(content[i], ' ', 0);
			if (!ft_strncmp(temp[0], "NO", 3) && cub->map->textures[NO] == 0)
				cub->map->textures[NO] = ft_strdup_until(temp[1], ft_strlen(temp[1]) - 1);
			else if (!ft_strncmp(temp[0], "SO", 3) && cub->map->textures[SO] == 0)
				cub->map->textures[SO] = ft_strdup_until(temp[1], ft_strlen(temp[1]) - 1);
			else if (!ft_strncmp(temp[0], "WE", 3) && cub->map->textures[WE] == 0)
				cub->map->textures[WE] = ft_strdup_until(temp[1], ft_strlen(temp[1]) - 1);
			else if (!ft_strncmp(temp[0], "EA", 3) && cub->map->textures[EA] == 0)
				cub->map->textures[EA] = ft_strdup_until(temp[1], ft_strlen(temp[1]) - 1);
			else if (!ft_strncmp(temp[0], "F", 2) && cub->map->floor_color == 0)
				cub->map->floor_color = rgb_to_hex(temp[1]);
			else if (!ft_strncmp(temp[0], "C", 2) && cub->map->ceil_color == 0)
				cub->map->ceil_color = rgb_to_hex(temp[1]);
			else
			{
				ft_freemtx(temp);
				ft_freemtx(content);
				ft_freemtx(cub->map->textures);
				free(cub->map);
				free(cub);
				ft_putstr_fd("Error\nIncorrectly defined textures\n", STDERR_FILENO);
				exit(41);
			}
			texture_posi++;
			ft_freemtx(temp);
		}
		else if (texture_posi > 5)
		{
			while (line_is_empty(content[++i]) == TRUE) ;
			return (i);
		}
		i++;
	}
	return(0);
}

void	get_map(t_cub *cub, char **content, int i_map)
{
	int	i;

	i = 0;
	while (line_is_empty(content[i_map]) == FALSE)
	{
		cub->map->map[i] = ft_strdup_until(content[i_map], ft_strlen(content[i_map]) - 1);
		i_map++;
		i++;
	}
}
