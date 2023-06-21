/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dofranci <dofranci@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 19:44:21 by jlucas-s          #+#    #+#             */
/*   Updated: 2023/06/20 21:59:10 by dofranci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	arg_validation(int argc, char *argv[])
{
	if (argc != 2)
	{
		ft_putstr_fd("Error\nIncorrect number of arguments. (Uninformed map)\n", \
		STDERR_FILENO);
		exit(10);
	}
	else if (!ft_strnstr(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 4))
	{
		ft_putstr_fd("Error\ninvalid map. (.cub)\n", STDERR_FILENO);
		exit(11);
	}
}

int line_is_empty(char *str)
{
	int i;

	i = 0;
	while(str[i] && str[i] != '\n')
	{
		if(str[i] != ' ' && str[i] != '\t')
			return (FALSE);	
		i++;
	}
	return (TRUE);
}

void	free_split(char **split)
{
	int	i;

	i = -1;
	if (!split)
		return ;
	while (split[++i])
		free(split[i]);
	free(split);
}

t_cub	*init_cub(char *file)
{
	int		fd;
	t_cub	*cub;
	char	*line;
	char	**temp;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		exit(20);

	cub = (t_cub *)malloc(sizeof(t_cub));
	cub->map = (t_map *)malloc(sizeof(t_map));
	cub->map->textures = malloc(sizeof(char *) * 7);
	line = get_next_line(fd);
	int i = 0;

	while (line)
	{
		if(line_is_empty(line) == FALSE)
		{
			if((ft_strnstr(line, "NO", ft_strlen(line)) && i == 0) || \
			   (ft_strnstr(line, "SO", ft_strlen(line)) && i == 1) || \
			   (ft_strnstr(line, "WE", ft_strlen(line)) && i == 2) || \
			   (ft_strnstr(line, "EA", ft_strlen(line)) && i == 3)|| \
			   (ft_strnstr(line, "F", ft_strlen(line)) && i == 4) || \
			   (ft_strnstr(line, "C", ft_strlen(line)) && i == 5))
			{
				temp = ft_split(line, ' ', 0);
				cub->map->textures[i] = ft_strdup_until(temp[1], ft_strlen(temp[1]) - 1);
				i++;
				free_split(temp);
			}
		}
		free(line);
		line = get_next_line(fd);
	}

	ft_printf("texture[0]:%s\n", cub->map->textures[NO]);
	ft_printf("texture[1]:%s\n", cub->map->textures[1]);
	ft_printf("texture[2]:%s\n", cub->map->textures[2]);
	ft_printf("texture[3]:%s\n", cub->map->textures[3]);
	ft_printf("texture[4]:%s\n", cub->map->textures[4]);
	ft_printf("texture[5]:%s\n", cub->map->textures[C]);
	return (cub);
}

int	main(int argc, char *argv[])
{
	t_cub	*cub;

	arg_validation(argc, argv);
	cub = init_cub(argv[1]);
	// map_validation();
	free(cub);
	return (0);
}