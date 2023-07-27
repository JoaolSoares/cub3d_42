/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-s <jlucas-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 19:44:21 by jlucas-s          #+#    #+#             */
/*   Updated: 2023/07/27 20:37:55 by jlucas-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void exit_cub(t_cub *cub, int i)
{
	if(i != 51)
	{
		mlx_destroy_window(cub->mlx->mlx, cub->mlx->win);
		mlx_destroy_display(cub->mlx->mlx);
		mlx_loop_end(cub->mlx->mlx);
		free(cub->mlx->mlx);
		free(cub->mlx);
	}
	ft_freemtx(cub->map->textures);
	ft_freemtx(cub->map->map);
	free(cub->player);
	free(cub->map);
	free(cub);

	exit(i);
}

static void set_data(t_cub *cub)
{ 
  cub->player = malloc(sizeof(t_player));
  cub->player->posx = (double)(cub->map->player_x * 16);
  cub->player->posy = (double)(cub->map->player_y * 16);
  // dependendo da letra do mapa vai mudar o angulo
  cub->player->deltaPosA = PI;
  cub->player->deltaPosX = cos(cub->player->deltaPosA) * 5;
  cub->player->deltaPosY = sin(cub->player->deltaPosA) * 5;
  // cub->player->dirX = -1;
  // cub->player->dirY = 0; 
  // cub->player->planeX = 0; 
  // cub->player->planeY = 0.66; 
  // cub->player->time = 0; 
  // cub->player->oldTime = 0; 
}

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
	set_data(cub);
	draw(cub);

	hook_handler(cub);
	exit_cub(cub, 0);
}
