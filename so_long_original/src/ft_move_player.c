/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 20:05:22 by atalaver          #+#    #+#             */
/*   Updated: 2022/12/15 21:39:41 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	ft_move_check_clear(int i, int j, t_mapa map)
{
	if (j >= map.width)
	{
		j = 0;
		i++;
	}
	if (map.mapa[i * map.width + j] == '0')
		return (1);
	return (0);
}

//Return 1 if the game is end, 0 continue
int	ft_move_right(t_game *game)
{
	mlx_put_image_to_window(game->vars.mlx, game->vars.win,
		game->spr.floor.img, game->player.x * 64, game->player.y * 64);
	game->player.x += 1;
	mlx_put_image_to_window(game->vars.mlx, game->vars.win,
		game->spr.player.img, game->player.x * 64, game->player.y * 64);
	return (0);
}

int	ft_move_left(t_game *game)
{
	mlx_put_image_to_window(game->vars.mlx, game->vars.win,
		game->spr.floor.img, game->player.x * 64, game->player.y * 64);
	game->player.x -= 1;
	mlx_put_image_to_window(game->vars.mlx, game->vars.win,
		game->spr.player.img, game->player.x * 64, game->player.y * 64);
	return (0);
}

int	ft_move_top(t_game *game)
{
	mlx_put_image_to_window(game->vars.mlx, game->vars.win,
		game->spr.floor.img, game->player.x * 64, game->player.y * 64);
	game->player.y -= 1;
	mlx_put_image_to_window(game->vars.mlx, game->vars.win,
		game->spr.player.img, game->player.x * 64, game->player.y * 64);
	return (0);
}

int	ft_move_down(t_game *game)
{
	mlx_put_image_to_window(game->vars.mlx, game->vars.win,
		game->spr.floor.img, game->player.x * 64, game->player.y * 64);
	game->player.y += 1;
	mlx_put_image_to_window(game->vars.mlx, game->vars.win,
		game->spr.player.img, game->player.x * 64, game->player.y * 64);
	return (0);
}
