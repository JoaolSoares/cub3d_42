/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-s <jlucas-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 19:44:21 by jlucas-s          #+#    #+#             */
/*   Updated: 2023/08/02 22:12:03 by jlucas-s         ###   ########.fr       */
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

int	main(int argc, char *argv[])
{
	t_cub	*cub;

	arg_validation(argc, argv);
	cub = (t_cub *)malloc(sizeof(t_cub));
	init_map(cub, argv[1]);
	map_validation(cub);
	init_mlx(cub);
	init_img(cub);
	init_player(cub);
	draw(cub);

	hook_handler(cub);
	exit_cub(cub, 0);
}
