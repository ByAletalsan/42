/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 11:06:19 by atalaver          #+#    #+#             */
/*   Updated: 2022/11/23 12:39:57 by atalaver         ###   ########.fr       */
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
t_mapa	ft_read_map(const char	*s)
{
	t_mapa	map;
	char	*str;
	int		f;

	f = open(s, O_RDONLY);
	str = get_next_line(f);
	map.mapa = (char *)malloc(1);
	map.mapa[0] = '\0';
	while (str)
	{
		map.mapa = ft_strjoin(map.mapa, str);
		str = get_next_line(f);
	}
	free(str);
	ft_size_map(&map);
	close(f);
	return (map);
}

//Cargo los sprites en un struct para tenerlos localizados
static	t_sprites	ft_load_sprites(t_vars vars)
{
	t_sprites	spr;

	spr.floor.img = mlx_xpm_file_to_image(vars.mlx, "./spr/grass.xpm",
			&spr.floor.width, &spr.floor.height);
	spr.wall.img = mlx_xpm_file_to_image(vars.mlx, "./spr/wall.xpm",
			&spr.wall.width, &spr.wall.height);
	spr.door[0].img = mlx_xpm_file_to_image(vars.mlx, "./spr/door.xpm",
			&spr.door[0].width, &spr.door[0].height);
	spr.door[1].img = mlx_xpm_file_to_image(vars.mlx, "./spr/floor.xpm",
			&spr.door[1].width, &spr.door[1].height);
	spr.door[2].img = mlx_xpm_file_to_image(vars.mlx, "./spr/door_close.xpm",
			&spr.door[1].width, &spr.door[1].height);
	spr.door[3].img = mlx_xpm_file_to_image(vars.mlx, "./spr/door_open.xpm",
			&spr.door[2].width, &spr.door[2].height);
	spr.chest.img = mlx_xpm_file_to_image(vars.mlx, "./spr/chest_close.xpm",
			&spr.chest.width, &spr.chest.height);
	return (spr);
}

static void	ft_print_sprite_map(int width, int height, char c, t_vars vars)
{
	t_sprites	spr;

	spr = ft_load_sprites(vars);
	if (c == '0')
		mlx_put_image_to_window(vars.mlx, vars.win, spr.floor.img,
			width * 64, height * 64);
	else if (c == '1')
		mlx_put_image_to_window(vars.mlx, vars.win, spr.wall.img,
			width * 64, height * 64);
	else if (c == 'C')
	{
		mlx_put_image_to_window(vars.mlx, vars.win, spr.floor.img,
			width * 64, height * 64);
		mlx_put_image_to_window(vars.mlx, vars.win, spr.chest.img,
			width * 64, height * 64);
	}
	else if (c == 'E')
	{
		mlx_put_image_to_window(vars.mlx, vars.win, spr.door[1].img,
			width * 64, height * 64);
		mlx_put_image_to_window(vars.mlx, vars.win, spr.door[0].img,
			width * 64, height * 64);
		mlx_put_image_to_window(vars.mlx, vars.win, spr.door[2].img,
			width * 64, height * 64);
	}
	else if (c == 'P')
		mlx_put_image_to_window(vars.mlx, vars.win, spr.floor.img,
			width * 64, height * 64);
}

//Renderizamos el mapa con los sprites correspondientes
void	ft_render_map(t_vars vars, t_mapa map)
{
	int			i;
	int			width;
	int			height;

	i = 0;
	width = 0;
	height = 0;
	while (map.mapa[i] != '\0')
	{
		if (map.mapa[i] == '\n')
		{
			height++;
			width = 0;
		}
		else
		{
			ft_print_sprite_map(width, height, map.mapa[i], vars);
			width++;
		}
		i++;
	}
}
