/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-s <jlucas-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 19:20:29 by jlucas-s          #+#    #+#             */
/*   Updated: 2023/06/26 21:22:12 by jlucas-s         ###   ########.fr       */
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

char	**get_file_content(char *file)
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
				exit(31);
			}
			ft_freemtx(temp);
		}
		else
			return (i);
		i++;
	}
	return(0);
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
	
	cub->map->map = ft_calloc(sizeof(char *) * (pick_file_size(file) - i_map), pick_file_size(file) - i_map);
	
	get_map(cub, file_content);



	// PRINT
	int i = -1;
	while (cub->map->textures[++i])
		ft_printf("tx[%i] = %s\n", i, cub->map->textures[i]);
	i = -1;
	// while (cub->map->map[++i])
	// 	ft_printf("map[%i] = |%s|\n", i, cub->map->map[i]);
	// PRINT

	ft_freemtx(file_content);
	return (cub);
}

