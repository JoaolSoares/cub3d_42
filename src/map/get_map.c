/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-s <jlucas-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 21:28:53 by jlucas-s          #+#    #+#             */
/*   Updated: 2023/08/15 22:32:41 by jlucas-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_map(t_cub *cub, char **content, int file_index)
{
	int	i;
	int	map_index;

	cub->map->height = 0;
	cub->map->width = 0;
	map_index = file_index;
	while (line_is_empty(content[map_index++]) == FALSE)
		cub->map->height++;
	cub->map->map = \
	ft_calloc(sizeof(char *) * cub->map->height + 1, cub->map->height + 1);
	i = 0;
	while (line_is_empty(content[file_index]) == FALSE)
	{
		cub->map->map[i] = ft_strdup_until(content[file_index], \
		ft_strlen(content[file_index]) - 1);
		file_index++;
		i++;
	}
	i = 0;
	while (cub->map->map[++i])
	{
		if ((int)ft_strlen(cub->map->map[i]) > cub->map->width)
			cub->map->width = ft_strlen(cub->map->map[i]);
		i++;
	}
}
