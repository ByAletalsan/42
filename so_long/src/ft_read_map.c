/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 11:06:19 by atalaver          #+#    #+#             */
/*   Updated: 2022/12/16 19:21:19 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

//Cargo los sprites en un struct para tenerlos localizados
void	ft_load_sprites(t_game *game)
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

static t_obj	*ft_create_obj(int _x, int _y, char _c)
{
	t_obj	*o;

	o = (t_obj *)malloc(sizeof(t_obj));
	if (!o)
		return (NULL);
	o->x = _x;
	o->y = _y;
	o->c = _c;
	return (o);
}

static void	ft_fill_obj(t_game *game)
{
	int		i;
	int		j;
	t_obj	*o;
	t_list	*l;

	i = 1;
	game->score = 0;
	game->frame = 0;
	game->steps = 0;
	while (i < game->map.height - 1)
	{
		j = 1;
		while (j < game->map.width - 1)
		{
			if (game->map.mapa[(i * (game->map.width + 1)) + j] != '0')
			{
				o = ft_create_obj(j, i,
						game->map.mapa[(i * (game->map.width + 1)) + j]);
				l = ft_lstnew(o);
				if (!ft_lstsize(game->obj))
					
					game->obj = l;
				else
					ft_lstadd_back(&game->obj, l);
				o->x = j * 64;
				o->y = i * 64;
				if (o->c == 'C')
					game->score += 1;
			}
			j++;
		}
		i++;
	}
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
	game->obj = NULL;
	ft_fill_obj(game);
	close(f);
}
