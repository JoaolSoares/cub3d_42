/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-s <jlucas-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 19:20:29 by jlucas-s          #+#    #+#             */
/*   Updated: 2023/06/21 20:58:56 by jlucas-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int line_is_empty(char *str)
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

static int	get_textures(t_map *map, char *line)
{
	static int	i;
	char		**temp;
	
	if (i <= 5)
	{
		temp = ft_split(line, ' ', 0);
		if ((ft_strnstr(temp[0], "NO", 3) && i == NO) ||	\
			(ft_strnstr(temp[0], "SO", 3) && i == SO) ||	\
			(ft_strnstr(temp[0], "WE", 3) && i == WE) ||	\
			(ft_strnstr(temp[0], "EA", 3) && i == EA) ||	\
			(ft_strnstr(temp[0], "F", 2) && i == F) ||		\
			(ft_strnstr(temp[0], "C", 2) && i == C))
		{
			map->textures[i] = ft_strdup_until(temp[1], ft_strlen(temp[1]) - 1);
			i++;
		}
		// else
		// {
			// retorno quando faltar uma textura
		// }
		ft_freemtx(temp);
		return (FALSE);
	}
	return (TRUE);
}

static int	pick_height(char *file)
{
	char	*buffer;
	int		i;
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		exit(20);

	buffer = get_next_line(fd);
	i = 0;
	if (line_is_empty(buffer) == FALSE)
		i = 1;
	while (buffer)
	{
		free(buffer);
		buffer = get_next_line(fd);
		if (line_is_empty(buffer) == FALSE)
			i++;
	}
	close(fd);
	return (i);
}

static t_map *get_map_infos(char *file)
{
	t_map	*map;
	char	*line;
	int		fd;
	int		i;

	i = 0;
	map = (t_map *)malloc(sizeof(t_map));
	map->textures = (char **)malloc(sizeof(char *) * 7);
	map->textures[6] = NULL;
	map->map = (char **)malloc(sizeof(char *) * (pick_height(file) - 5));
	map->map[pick_height(file) - 6] = NULL;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		exit(20);

	line = get_next_line(fd);
	while (line)
	{
		if(line_is_empty(line) == FALSE)
			if (get_textures(map, line) == TRUE)
				map->map[i++] = ft_strdup_until(line, ft_strlen(line) - 1);
	
		free(line);
		line = get_next_line(fd);
	}
	
	return (map);
}

t_cub	*init_cub(char *file)
{
	// int		fd;
	t_cub	*cub;

	cub = (t_cub *)malloc(sizeof(t_cub));
	cub->map = get_map_infos(file);

	// PRINT
	// int i = -1;
	// while (cub->map->textures[++i])
	// 	ft_printf("tx[%i] = %s\n", i, cub->map->textures[i]);
	// i = -1;
	// while (cub->map->map[++i])
	// 	ft_printf("map[%i] = |%s|\n", i, cub->map->map[i]);
	// PRINT

	return (cub);
}
