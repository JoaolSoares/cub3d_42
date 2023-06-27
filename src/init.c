/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-s <jlucas-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 19:20:29 by jlucas-s          #+#    #+#             */
/*   Updated: 2023/06/26 21:58:22 by jlucas-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	pick_file_size(char *file)
{
	char	*buffer;
	int		i;
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		exit(22);

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
	
	file_content = (char **)malloc(sizeof(char *) * (pick_file_size(file) + 1));
	fd = open(file, O_RDONLY);
	if (fd < 0)
		exit(21);
	file_content[0] = get_next_line(fd);
	i = 1;
	while(file_content[i - 1])
		file_content[i++] = get_next_line(fd);
	return(file_content);
}

t_cub	*init_cub(char *file)
{
	t_cub	*cub;
	int		i_map;
	char	**file_content;

	file_content = get_file_content(file);

	cub = (t_cub *)malloc(sizeof(t_cub));
	cub->map = (t_map *)malloc(sizeof(t_map));
	cub->map->textures = ft_calloc(sizeof(char *) * 7, 7);

	i_map = get_textures(cub, file_content);
	
	// isso não da o tamanho do mapa real, não considera linhas vazias antes e dps do mapa
	cub->map->map = ft_calloc(sizeof(char *) * (pick_file_size(file) - i_map), pick_file_size(file) - i_map);
	
	// get_map(cub, file_content, i_map);



	// PRINT
	int i = -1;
	while (cub->map->textures[++i])
		ft_printf("tx[%i] = %s\n", i, cub->map->textures[i]);
	i = -1;
	while (cub->map->map[++i])
		ft_printf("map[%i] = |%s|\n", i, cub->map->map[i]);
	// PRINT

	ft_freemtx(file_content);
	return (cub);
}

