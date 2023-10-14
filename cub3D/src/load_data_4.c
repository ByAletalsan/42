/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_data_4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 19:39:09 by dvasco-m          #+#    #+#             */
/*   Updated: 2023/10/03 20:07:11 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static int	check_closed_map(char **map, int x, int y)
{
	if (map[y][x] == '1')
		return (0);
	if (y == 0 || y == ft_len_matrix2(map) - 1
		|| x == 0 || x == (int)ft_strlen(map[y]))
		return (1);
	map[y][x] = '1';
	if (map[y + 1][x] != '1' && check_closed_map(map, x, y + 1))
		return (1);
	if (map[y - 1][x] != '1' && check_closed_map(map, x, y - 1))
		return (1);
	if (map[y][x + 1] != '1' && check_closed_map(map, x + 1, y))
		return (1);
	if (map[y][x - 1] != '1' && check_closed_map(map, x - 1, y))
		return (1);
	return (0);
}

static void	condition_characters_map(char c, int *invalid, int *init_pos)
{
	if (c != '1' && c != '0' && c != ' ' && c != 'N' && c != 'S'
		&& c != 'E' && c != 'W' && c != 'P')
		*invalid = 1;
	else if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		*init_pos += 1;
}

static void	find_position_player(t_data_map *map)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	while (map->map && map->map[i])
	{
		j = 0;
		while (map->map[i][j])
		{
			c = map->map[i][j];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				map->pos_x = j;
				map->pos_y = i;
				map->orientation = c;
				return ;
			}
			j++;
		}
		i++;
	}
}

int	check_valid_map(t_data_map *map)
{
	int		invalid;
	int		init_pos;
	int		i;
	int		j;
	char	**aux;

	invalid = 0;
	init_pos = 0;
	i = -1;
	while (map->map && (map->map)[++i] && !invalid && init_pos < 2)
	{
		j = 0;
		while (map->map && (map->map)[i][j])
			condition_characters_map((map->map)[i][j++], &invalid, &init_pos);
	}
	if (init_pos != 1)
		invalid = 1;
	if (invalid)
		return (1);
	find_position_player(map);
	aux = ft_dup_matrix(map->map);
	if (!aux)
		return (1);
	i = check_closed_map(aux, map->pos_x, map->pos_y);
	return (ft_free_params(aux), i);
}

void	init_map(t_data_map *map)
{
	map->no = NULL;
	map->we = NULL;
	map->so = NULL;
	map->ea = NULL;
	map->map = NULL;
	map->f = 0;
	map->c = 0;
}
