/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-s <jlucas-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 19:20:29 by jlucas-s          #+#    #+#             */
/*   Updated: 2023/06/28 21:03:09 by jlucas-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_file_size(char *file)
{
	char	*buffer;
	int		i;
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Error\nunable to read map\n", STDERR_FILENO);
		exit(31);
	}
	buffer = get_next_line(fd);
	i = 0;
	while (buffer)
	{
		i++;
		free(buffer);
		buffer = get_next_line(fd);
	}
	close(fd);
	return (i);
}

static char	**get_file_content(char *file)
{
	int		fd;
	int		i;
	char	**file_content;

	file_content = (char **)malloc(sizeof(char *) * (get_file_size(file) + 1));
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Error\nunable to read map\n", STDERR_FILENO);
		exit(21);
	}
	i = 0;
	file_content[i] = get_next_line(fd);
	while(file_content[++i - 1])
		file_content[i] = get_next_line(fd);
	return(file_content);
}

void	init_map(t_cub *cub, char *file)
{
	int		i_map;
	char	**file_content;

	file_content = get_file_content(file);

	cub->map = (t_map *)malloc(sizeof(t_map));
	cub->map->textures = ft_calloc(sizeof(char *) * 7, 7);

	i_map = get_textures(cub, file_content);
	
	cub->map->height = 0;
	while (line_is_empty(file_content[i_map++]) == FALSE)
		cub->map->height++;

	cub->map->map = ft_calloc(sizeof(char *) * cub->map->height + 1, cub->map->height + 1);
	
	get_map(cub, file_content, i_map - cub->map->height - 1);

	// pensar em tirar
	cub->map->width = 0;
	i_map = -1;
	while (cub->map->map[++i_map])
		if ((int)ft_strlen(cub->map->map[i_map]) > cub->map->width)
			cub->map->width = ft_strlen(cub->map->map[i_map]);
	// pensar em tirar

	ft_freemtx(file_content);
}
