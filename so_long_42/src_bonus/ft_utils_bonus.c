/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 21:16:13 by atalaver          #+#    #+#             */
/*   Updated: 2023/02/08 20:16:08 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	ft_check_limit(t_mapa map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map.height)
	{
		j = 0;
		while (j < map.width)
		{
			if (i == 0 && map.mapa[j] != '1')
				return (1);
			else if (i == map.height - 1
				&& map.mapa[(i * (map.width + 1)) + j] != '1')
				return (1);
			else if ((j == 0 || j == map.width - 1)
				&& map.mapa[(i * (map.width + 1)) + j] != '1')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

static void	ft_load_enemi_spr(t_game *game)
{
	game->spr.enemi[0].img = mlx_xpm_file_to_image(game->vars.mlx,
			"./spr/enemi/idle1.xpm", &game->spr.enemi[0].width,
			&game->spr.enemi[0].height);
	game->spr.enemi[1].img = mlx_xpm_file_to_image(game->vars.mlx,
			"./spr/enemi/idle2.xpm", &game->spr.enemi[1].width,
			&game->spr.enemi[1].height);
	game->spr.enemi[2].img = mlx_xpm_file_to_image(game->vars.mlx,
			"./spr/enemi/idle3.xpm", &game->spr.enemi[2].width,
			&game->spr.enemi[2].height);
	game->spr.enemi[3].img = mlx_xpm_file_to_image(game->vars.mlx,
			"./spr/enemi/idle4.xpm", &game->spr.enemi[3].width,
			&game->spr.enemi[3].height);
}

static void	ft_load_more_sprites(t_game *game)
{
	game->spr.chest.img = mlx_xpm_file_to_image(game->vars.mlx,
			"./spr/chest_close.xpm", &game->spr.chest.width,
			&game->spr.chest.height);
	game->spr.player[0].img = mlx_xpm_file_to_image(game->vars.mlx,
			"./spr/player/player_left.xpm",
			&game->spr.player[0].width, &game->spr.player[0].height);
	game->spr.player[1].img = mlx_xpm_file_to_image(game->vars.mlx,
			"./spr/player/player_top.xpm",
			&game->spr.player[1].width, &game->spr.player[1].height);
	game->spr.player[2].img = mlx_xpm_file_to_image(game->vars.mlx,
			"./spr/player/player_right.xpm",
			&game->spr.player[0].width, &game->spr.player[0].height);
	game->spr.player[3].img = mlx_xpm_file_to_image(game->vars.mlx,
			"./spr/player/player_down.xpm",
			&game->spr.player[0].width, &game->spr.player[0].height);
}

static void	ft_load_sprites(t_game *game)
{
	game->spr.floor.img = mlx_xpm_file_to_image(game->vars.mlx,
			"./spr/grass.xpm", &game->spr.floor.width, &game->spr.floor.height);
	game->spr.wall.img = mlx_xpm_file_to_image(game->vars.mlx,
			"./spr/wall.xpm", &game->spr.wall.width, &game->spr.wall.height);
	game->spr.door[0].img = mlx_xpm_file_to_image(game->vars.mlx,
			"./spr/door.xpm", &game->spr.door[0].width,
			&game->spr.door[0].height);
	game->spr.door[1].img = mlx_xpm_file_to_image(game->vars.mlx,
			"./spr/floor.xpm", &game->spr.door[1].width,
			&game->spr.door[1].height);
	game->spr.door[2].img = mlx_xpm_file_to_image(game->vars.mlx,
			"./spr/door_close.xpm", &game->spr.door[1].width,
			&game->spr.door[1].height);
	game->spr.door[3].img = mlx_xpm_file_to_image(game->vars.mlx,
			"./spr/door_open.xpm", &game->spr.door[2].width,
			&game->spr.door[2].height);
}

void	ft_load(t_game *game)
{
	ft_load_sprites(game);
	ft_load_more_sprites(game);
	ft_load_enemi_spr(game);
	game->frame = 0;
	game->steps = 0;
	game->direction = 4;
	game->pasos = 0;
	game->keys[0] = 0;
	game->keys[1] = 13;
	game->keys[2] = 2;
	game->keys[3] = 1;
	game->frame_enemi = 0;
}
