/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 10:26:12 by atalaver          #+#    #+#             */
/*   Updated: 2023/02/08 21:01:02 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	key_hook(int keycode, t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (keycode == game->keys[i])
		{
			game->move = 1;
			if (!game->pasos)
			{
				if (game->direction != i + 1)
					game->direction = i + 1;
				else
					game->pasos += 1;
			}
		}
		i++;
	}
	if (keycode == 53)
		ft_free_game(game);
	return (0);
}

int	key_hook_up(int keycode, t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (keycode == game->keys[i])
		{
			game->move = 0;
		}
		i++;
	}
	if (keycode == 53)
		ft_free_game(game);
	return (0);
}

//14.000 fps / 120 fps = 116
int	animation(t_game *game)
{
	int	i;

	i = 0;
	ft_render_map(game);
	if (game->pasos)
	{
		while (i++ < 2)
		{
			if (game->direction == 3)
				ft_move(game, 1, 0);
			else if (game->direction == 1)
				ft_move(game, -1, 0);
			else if (game->direction == 2)
				ft_move(game, 0, -1);
			else if (game->direction == 4)
				ft_move(game, 0, 1);
		}
		game->pasos += 1;
		if (game->pasos == 9 && game->move)
			game->pasos = 1;
		if (game->pasos == 9)
			game->pasos = 0;
	}
	ft_reset_frames(game);
	return (0);
}

static void	ft_map(t_game *game, char *s)
{
	if (!ft_check_ber(s))
	{
		if (!ft_read_map(s, game))
		{
			ft_printf("Error\nNo existe el archivo\n");
			exit(1);
		}
	}
	else
	{
		ft_printf("Error\nFormato incorrecto\n");
		exit(1);
	}
	if (ft_check_map(*game))
	{
		free(game->map.mapa);
		ft_free_obj(game);
		exit(1);
	}
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		ft_printf("%s <mapa.ber>\n", argv[0]);
		exit(1);
	}
	ft_map(&game, argv[1]);
	game.move = 0;
	game.vars.mlx = mlx_init();
	game.vars.win = mlx_new_window(game.vars.mlx, game.map.width * 64,
			game.map.height * 64, "./so_long");
	ft_load(&game);
	mlx_hook(game.vars.win, 2, (1L << 0), key_hook, &game);
	mlx_hook(game.vars.win, 3, (1L << 0), key_hook_up, &game);
	mlx_hook(game.vars.win, 17, (1L << 0), ft_free_game, &game);
	mlx_loop_hook(game.vars.mlx, animation, &game);
	mlx_loop(game.vars.mlx);
	return (0);
}
