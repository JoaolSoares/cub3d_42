/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_infos.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-s <jlucas-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 21:28:53 by jlucas-s          #+#    #+#             */
/*   Updated: 2023/06/27 21:16:04 by jlucas-s         ###   ########.fr       */
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
			if ((!ft_strncmp(temp[0], "NO", 3) && texture_posi == NO) ||	\
				(!ft_strncmp(temp[0], "SO", 3) && texture_posi == SO) ||	\
				(!ft_strncmp(temp[0], "WE", 3) && texture_posi == WE) ||	\
				(!ft_strncmp(temp[0], "EA", 3) && texture_posi == EA) ||	\
				(!ft_strncmp(temp[0], "F", 2) && texture_posi == F) ||		\
				(!ft_strncmp(temp[0], "C", 2) && texture_posi == C))
			{
				cub->map->textures[texture_posi] = ft_strdup_until(temp[1], ft_strlen(temp[1]) - 1);
				texture_posi++;
			}
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