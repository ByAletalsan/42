/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 11:06:19 by atalaver          #+#    #+#             */
/*   Updated: 2022/12/15 21:19:46 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

//Calculamos el tamano del mapa
static void	ft_size_map(t_mapa *map)
{
	int	i;
	int	height;

	i = 0;
	height = 0;
	while (map->mapa[i] != '\0' && map->mapa[i] != '\n')
		i++;
	map->width = i;
	i = 0;
	while (map->mapa[i] != '\0')
	{
		if (map->mapa[i] == '\n')
			height++;
		i++;
	}
	map->height = height + 1;
}

//Leemos el mapa y lo guardamos con un struct sus datos
void	ft_read_map(const char	*s, t_game *game)
{
	char	*str;
	int		f;

	f = open(s, O_RDONLY);
	str = get_next_line(f);
	game->map.mapa = (char *)malloc(1);
	game->map.mapa[0] = '\0';
	while (str)
	{
		game->map.mapa = ft_strjoin(game->map.mapa, str);
		str = get_next_line(f);
	}
	free(str);
	ft_size_map(&game->map);
	close(f);
	ft_find_position_player(game);
}

//Cargo los sprites en un struct para tenerlos localizados
static	void	ft_load_sprites(t_game *game)
{
	game->spr.floor.img = mlx_xpm_file_to_image(game->vars.mlx, "./spr/grass.xpm",
			&game->spr.floor.width, &game->spr.floor.height);
	game->spr.wall.img = mlx_xpm_file_to_image(game->vars.mlx, "./spr/wall.xpm",
			&game->spr.wall.width, &game->spr.wall.height);
	game->spr.door[0].img = mlx_xpm_file_to_image(game->vars.mlx, "./spr/door.xpm",
			&game->spr.door[0].width, &game->spr.door[0].height);
	game->spr.door[1].img = mlx_xpm_file_to_image(game->vars.mlx, "./spr/floor.xpm",
			&game->spr.door[1].width, &game->spr.door[1].height);
	game->spr.door[2].img = mlx_xpm_file_to_image(game->vars.mlx, "./spr/door_close.xpm",
			&game->spr.door[1].width, &game->spr.door[1].height);
	game->spr.door[3].img = mlx_xpm_file_to_image(game->vars.mlx, "./spr/door_open.xpm",
			&game->spr.door[2].width, &game->spr.door[2].height);
	game->spr.chest.img = mlx_xpm_file_to_image(game->vars.mlx, "./spr/chest_close.xpm",
			&game->spr.chest.width, &game->spr.chest.height);
	game->spr.player.img = mlx_xpm_file_to_image(game->vars.mlx, "./spr/player.xpm",
			&game->spr.player.width, &game->spr.player.height);
}

static void	ft_print_sprite_map(int width, int height, char c, t_game *game)
{
	ft_load_sprites(game);
	if (c == '0')
		mlx_put_image_to_window(game->vars.mlx, game->vars.win,
			game->spr.floor.img, width * 64, height * 64);
	else if (c == '1')
		mlx_put_image_to_window(game->vars.mlx, game->vars.win,
			game->spr.wall.img, width * 64, height * 64);
	else if (c == 'C')
	{
		mlx_put_image_to_window(game->vars.mlx, game->vars.win,
			game->spr.floor.img, width * 64, height * 64);
		mlx_put_image_to_window(game->vars.mlx, game->vars.win,
			game->spr.chest.img, width * 64, height * 64);
	}
	else if (c == 'E')
	{
		mlx_put_image_to_window(game->vars.mlx, game->vars.win,
			game->spr.door[1].img, width * 64, height * 64);
		mlx_put_image_to_window(game->vars.mlx, game->vars.win,
			game->spr.door[0].img, width * 64, height * 64);
		mlx_put_image_to_window(game->vars.mlx, game->vars.win,
			game->spr.door[2].img, width * 64, height * 64);
	}
	else if (c == 'P')
	{
		mlx_put_image_to_window(game->vars.mlx, game->vars.win,
			game->spr.floor.img, width * 64, height * 64);
		mlx_put_image_to_window(game->vars.mlx, game->vars.win,
			game->spr.player.img, width * 64, height * 64);
	}
}

//Renderizamos el mapa con los sprites correspondientes
void	ft_render_map(t_game *game)
{
	int			i;
	int			width;
	int			height;

	i = 0;
	width = 0;
	height = 0;
	while (game->map.mapa[i] != '\0')
	{
		if (game->map.mapa[i] == '\n')
		{
			height++;
			width = 0;
		}
		else
		{
			ft_print_sprite_map(width, height, game->map.mapa[i], game);
			width++;
		}
		i++;
	}
}
