/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 10:26:12 by atalaver          #+#    #+#             */
/*   Updated: 2022/12/16 21:26:51 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	key_hook(int keycode, t_game *game)
{
	if (keycode == 100)
	{
		if (ft_move_right(game))
			exit(1);
	}
	if (keycode == 97)
	{
		if (ft_move_left(game))
			exit(1);
	}
	if (keycode == 119)
	{
		if (ft_move_top(game))
			exit(1);
	}
	if (keycode == 115)
	{
		if (ft_move_down(game))
			exit(1);
	}
	if (keycode == 65307)
	{
		ft_printf("Salimos!\n");
		mlx_destroy_window(game->vars.mlx, game->vars.win);
		exit(1);
	}
	return (0);
}

//14.000 fps / 120 fps = 116
int	animation(t_game *game)
{
	game->frame += 1;
	//ft_printf("Frame:%i\n", game->frame);
	if (game->frame % 116 == 0)
		ft_render_map(game);
	if (game->frame == 14000)
		game->frame = 0;
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		perror("Numero incorrecto de argumentos");
		exit(1);
	}
	if (!ft_check_ber(argv[1]))
		ft_read_map(argv[1], &game);
	else
	{
		ft_printf("Error\n");
		exit(1);
	}
	if (ft_check_map(game.map.mapa))
	{
		ft_printf("Error\n");
		free(game.map.mapa);
		exit(1);
	}
	game.vars.mlx = mlx_init();
	game.vars.win = mlx_new_window(game.vars.mlx, game.map.width * 64,
			game.map.height * 64, "./so_long");
	ft_load_sprites(&game);
	mlx_hook(game.vars.win, 2, (1L << 0), key_hook, &game);
	mlx_loop_hook(game.vars.mlx, animation, &game);
	mlx_loop(game.vars.mlx);
	free(game.map.mapa);
	ft_lstclear(&game.obj, NULL);
	return (0);
}
