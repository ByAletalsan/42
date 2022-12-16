/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 10:26:12 by atalaver          #+#    #+#             */
/*   Updated: 2022/12/15 21:20:11 by atalaver         ###   ########.fr       */
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
	else if (keycode == 97)
	{
		if (ft_move_left(game))
			exit(1);
	}
	else if (keycode == 119)
	{
		if (ft_move_top(game))
			exit(1);
	}
	else if (keycode == 115)
	{
		if (ft_move_down(game))
			exit(1);
	}
	else if (keycode == 65307)
	{
		ft_printf("Salimos!\n");
		mlx_destroy_window(game->vars.mlx, game->vars.win);
		exit(1);
	}
	return (0);
}

int	animation(t_vars *vars)
{
	(void) vars;
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
	//ft_printf("%s\n", map.mapa);
	if (ft_check_map(game.map.mapa))
	{
		ft_printf("Error\n");
		free(game.map.mapa);
		exit(1);
	}
	game.vars.mlx = mlx_init();
	game.vars.win = mlx_new_window(game.vars.mlx, game.map.width * 64,
			game.map.height * 64, "./so_long");
	ft_render_map(&game);
	mlx_hook(game.vars.win, 2, (1L << 0), key_hook, &game);
	mlx_loop_hook(game.vars.mlx, animation, &game.vars);
	mlx_loop(game.vars.mlx);
	free(game.map.mapa);
	return (0);
}
