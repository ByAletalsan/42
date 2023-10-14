/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 10:33:30 by atalaver          #+#    #+#             */
/*   Updated: 2023/02/08 16:34:51 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_check_ber(const char *s)
{
	int	len;

	len = ft_strlen(s);
	if (len < 4)
		return (1);
	if (s[len - 1] != 'r' || s[len - 2] != 'e' || s[len - 3] != 'b'
		|| s[len - 4] != '.')
		return (1);
	return (0);
}

static int	ft_check_rectangular(const char *s)
{
	int	i;
	int	width;
	int	len;

	i = 0;
	while (s[i] != '\0' && s[i] != '\n')
		i++;
	width = i;
	i++;
	len = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\n')
		{
			if (len != width)
				return (1);
			len = -1;
		}
		len++;
		i++;
	}
	if (len != 0 && len != width)
		return (1);
	return (0);
}

static int	ft_fill_elem(int *elem, char c)
{
	if (c == 'C')
		elem[0]++;
	else if (c == 'E')
		elem[1]++;
	else if (c == 'P')
		elem[2]++;
	else if (c != '\n' && c != '0' && c != '1')
		return (1);
	return (0);
}

static int	ft_check_elem(const char *s)
{
	int	elem[3];
	int	i;

	i = 0;
	while (i < 3)
		elem[i++] = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (ft_fill_elem(elem, s[i]))
			return (1);
		i++;
	}
	i = -1;
	while (++i < 3)
	{
		if (elem[i] != 1)
		{
			if (i > 0)
				return (1);
			if (i == 0 && elem[i] == 0)
				return (1);
		}
	}
	return (0);
}

int	ft_check_map(t_game game)
{
	t_obj	*player;
	char	*map_cp;
	int		i;

	player = ft_find_player(game.obj);
	i = 0;
	if (ft_check_rectangular(game.map.mapa))
		return (ft_printf("Error\nMapa no rectangular\n"), 1);
	if (ft_check_elem(game.map.mapa))
		return (ft_printf("Error\nMapa con elementos incorrectos\n"), 1);
	if (ft_check_limit(game.map))
		return (ft_printf("Error\nMapa con diferentes longitudes de linea\n"), 1);
	map_cp = ft_strdup(game.map.mapa);
	if (ft_check_ruta(game, player->x / 64, player->y / 64, map_cp))
		return (ft_printf("Error\nNo existe ruta a puerta\n"), 1);
	while (i++ < game.score)
	{
		free(map_cp);
		map_cp = NULL;
		map_cp = ft_strdup(game.map.mapa);
		if (ft_check_cofres(game, player->x / 64, player->y / 64, map_cp))
			return (ft_printf("Error\nNo existe ruta a cofre\n"), 1);
	}
	free(map_cp);
	return (0);
}
