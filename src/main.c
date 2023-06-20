/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-s <jlucas-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 19:44:21 by jlucas-s          #+#    #+#             */
/*   Updated: 2023/06/19 21:53:32 by jlucas-s         ###   ########.fr       */
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

t_cub	*init_cub(char *file)
{
	int		fd;
	t_cub	*cub;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		exit(20);

	cub = (t_cub *)malloc(sizeof(t_cub));
	cub->map = (t_map *)malloc(sizeof(t_map));
	cub->map->tx = (t_texture *)malloc(sizeof(t_texture));

	line = get_next_line(fd);
	while (line)
	{
		// ir lendo as linhas e adicionando as variaveis no mapa e texturas
		free(line);
		line = get_next_line(fd);
	}

	return (cub);
}

int	main(int argc, char *argv[])
{
	t_cub	*cub;

	arg_validation(argc, argv);
	cub = init_cub(argv[1]);
	// map_validation();

	return (0);
}