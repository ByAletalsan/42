/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 18:46:46 by asalas-s          #+#    #+#             */
/*   Updated: 2022/07/28 13:23:15 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"structs.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int	ft_atoi(const char *str);
int	ft_row_file_len(char *str);

char	**ft_load_map(int height, int width, int *file_open)
{
	char	*p;
	char	**map;
	int		i;
	int		j;
	char	buffer;

	map = malloc(sizeof(char *) * height);
	i = 0;
	while (i < height)
	{
		p = malloc(sizeof(char) * (width - 1));
		j = 0;
		while (j < width)
		{
			read(*file_open, &buffer, 1);
			p[j] = buffer;
			j++;
		}
		map[i] = p;
		i++;
	}
	close(*file_open);
	return (map);
}

int	ft_find_width(int file_open)
{
	int		count;
	char	buffer;
	int		c_r;

	count = 0;
	c_r = read(file_open, &buffer, 1);
	if (buffer < 32 || buffer > 126)
		return (0);
	while (buffer != '\n' && c_r > 0)
	{
		count++;
		c_r = read(file_open, &buffer, 1);
	}
	return (count + 1);
}

void	ft_load_condition(struct s_map *map_info, int *file_open, int len_row)
{
	char	buffer;
	int		number;
	int		i;

	i = 0;
	buffer = '0';
	number = 0;
	read(*file_open, &buffer, 1);
	while (i++ < (len_row - 4))
	{
		number *= 10;
		number += (buffer - '0');
		read(*file_open, &buffer, 1);
	}
	map_info->height = number;
	map_info->char_empty = buffer;
	read(*file_open, &buffer, 1);
	map_info->char_obstacle = buffer;
	read(*file_open, &buffer, 1);
	map_info->char_full = buffer;
	read(*file_open, &buffer, 1);
	map_info->width = ft_find_width(*file_open);
}

void	ft_load(struct s_map *map_info, char *str)
{
	int		file_open;
	char	buffer;

	file_open = open(str, O_RDONLY);
	ft_load_condition(map_info, &file_open, ft_row_file_len(str));
	close(file_open);
	file_open = open(str, O_RDONLY);
	read(file_open, &buffer, 1);
	while (buffer != '\n')
	{
		read(file_open, &buffer, 1);
	}
	map_info->map = ft_load_map(map_info->height, map_info->width, &file_open);
	close(file_open);
	return ;
}

void	ft_free_memory(struct s_map *map_info)
{
	int	i;

	i = 0;
	while (i < map_info->height)
	{
		free(map_info->map[i]);
		map_info->map[i] = NULL;
		i++;
	}
	map_info->char_empty = 0;
	map_info->char_full = 0;
	map_info->char_obstacle = 0;
	map_info->height = 0;
	map_info->width = 0;
	free(map_info->map);
	map_info->map = NULL;
}
