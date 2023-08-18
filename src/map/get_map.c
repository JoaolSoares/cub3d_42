/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-s <jlucas-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 21:28:53 by jlucas-s          #+#    #+#             */
/*   Updated: 2023/08/17 22:21:27 by jlucas-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_map(t_cub *cub, char **content, int file_index)
{
	int		i;
	int		map_index;
	char	*trim;

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
		trim = ft_strtrim(content[file_index], "\n");
		cub->map->map[i] = ft_strdup(trim);
		free(trim);
		file_index++;
		i++;
	}
	i = -1;
	while (cub->map->map[++i])
		if ((int)ft_strlen(cub->map->map[i]) > cub->map->width)
			cub->map->width = ft_strlen(cub->map->map[i]);
}
