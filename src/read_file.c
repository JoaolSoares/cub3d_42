/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-s <jlucas-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 19:20:29 by jlucas-s          #+#    #+#             */
/*   Updated: 2023/08/09 23:08:21 by jlucas-s         ###   ########.fr       */
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

void	read_file(t_cub *cub, char *file)
{
	int		file_index;
	char	**file_content;

	file_content = get_file_content(file);

	cub->map = (t_map *)malloc(sizeof(t_map));
	cub->map->textures_paths = ft_calloc(sizeof(char *) * 5, 5);

	cub->map->ceil_color = 0;
	cub->map->floor_color = 0;
	get_textures_path(cub, file_content, &file_index);

	cub->map->height = 0;
	cub->map->width = 0;
	get_map(cub, file_content, file_index);

	ft_freemtx(file_content);
}
