/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 17:37:51 by atalaver          #+#    #+#             */
/*   Updated: 2022/07/27 22:33:12 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"structs.h"
#include<unistd.h>
#include<stdio.h>

void	ft_reset(int *i, int *i_f, int *j_f, struct s_square square);

int	ft_control(struct s_map map_info, int i, int j)
{
	if (map_info.map[i][j] == map_info.char_obstacle)
		return (1);
	return (0);
}

void	ft_atribut_square(struct s_square *square, int i_f, int j_f)
{
	square->x_f = j_f - 1;
	square->y_f = i_f - 1;
	square->area = (j_f - square->x_i) * (i_f - square->y_i);
}

struct s_square	ft_search_square(int i, int j, struct s_map map_info)
{
	struct s_square	square;
	int				i_f;
	int				j_f;
	int				control;

	square.x_i = j;
	square.y_i = i;
	i_f = i + 1;
	j_f = j + 1;
	control = 0;
	while (i < i_f && i < map_info.height)
	{
		j = square.x_i;
		while (j < j_f && j < map_info.width)
		{
			if (ft_control(map_info, i, j++))
				break ;
		}
		if (ft_control(map_info, i, (j - 1)) || j == map_info.width)
			break ;
		i++;
		ft_reset(&i, &i_f, &j_f, square);
	}
	ft_atribut_square(&square, i_f, j_f);
	return (square);
}

void	ft_fill_square(struct s_square square, struct s_map *map_info)
{
	int	i;
	int	j;

	i = square.y_i;
	while (i < square.y_f)
	{
		j = square.x_i;
		while (j < square.x_f)
		{
			map_info->map[i][j] = map_info->char_full;
			j++;
		}
		i++;
	}
}

int	ft_fill_map(struct s_map *map_info)
{
	int				i;
	int				j;
	struct s_square	square;
	struct s_square	posible_square;

	square.area = 0;
	i = -1;
	while (++i < map_info->height)
	{
		j = 0;
		while (j < map_info->width)
		{
			if (map_info->map[i][j] == map_info->char_empty)
			{
				posible_square = ft_search_square(i, j, *map_info);
				if (posible_square.area > square.area)
				{
					square = posible_square;
				}
			}
			j++;
		}
	}
	ft_fill_square(square, map_info);
	return (1);
}
