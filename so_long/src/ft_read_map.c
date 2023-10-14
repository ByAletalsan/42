/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 11:06:19 by atalaver          #+#    #+#             */
/*   Updated: 2023/02/08 21:00:02 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

//Calculamos el tamano del mapa
static void	ft_size_map(t_mapa *map)
{
	int	i;
	int	height;
	int	count;

	i = 0;
	height = 0;
	while (map->mapa[i] != '\0' && map->mapa[i] != '\n')
		i++;
	map->width = i;
	i = 0;
	count = 0;
	while (map->mapa[i] != '\0')
	{
		if (count && map->mapa[i] == '\n')
		{
			height++;
			count = 0;
		}
		else
			count++;
		i++;
	}
	if (count)
		height++;
	map->height = height;
}

static t_obj	*ft_create_obj(int _x, int _y, t_game *game)
{
	t_obj	*o;
	char	c;

	c = game->map.mapa[(_y * (game->map.width + 1)) + _x];
	o = (t_obj *)malloc(sizeof(t_obj));
	if (!o)
		return (NULL);
	o->x = _x * 64;
	o->y = _y * 64;
	o->c = c;
	if (c == 'C')
		game->score += 1;
	return (o);
}

static void	ft_fill_obj(t_game *game)
{
	int		i;
	int		j;
	t_list	*l;

	i = 1;
	game->score = 0;
	while (i < game->map.height - 1)
	{
		j = 1;
		while (j < game->map.width - 1)
		{
			if (game->map.mapa[(i * (game->map.width + 1)) + j] != '0')
			{
				l = ft_lstnew(ft_create_obj(j, i, game));
				if (!ft_lstsize(game->obj))
					game->obj = l;
				else
					ft_lstadd_back(&game->obj, l);
			}
			j++;
		}
		i++;
	}
}

static char	*ft_add_and_free(char *str, char *buff)
{
	char	*r;

	r = ft_strjoin(str, buff);
	free(str);
	return (r);
}

//Leemos el mapa y lo guardamos con un struct sus datos
int	ft_read_map(const char	*s, t_game *game)
{
	char	*str;
	int		f;

	f = open(s, O_RDONLY);
	if (f < 0)
		return (0);
	str = get_next_line(f);
	game->map.mapa = (char *)malloc(1);
	game->map.mapa[0] = '\0';
	while (str)
	{
		game->map.mapa = ft_add_and_free(game->map.mapa, str);
		free(str);
		str = get_next_line(f);
	}
	free(str);
	ft_size_map(&game->map);
	game->obj = NULL;
	ft_fill_obj(game);
	close(f);
	return (1);
}
