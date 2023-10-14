/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_data_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 19:32:38 by dvasco-m          #+#    #+#             */
/*   Updated: 2023/09/29 18:08:14 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static int	check_ids_2(int *check, char *id)
{
	if (!ft_strcmp("EA", id) && !(*(check + 3)))
	{
		*(check + 3) = 1;
		return (0);
	}
	else if (!ft_strcmp("EA", id) && (*(check + 3)))
		return (1);
	if (!ft_strcmp("F", id) && !(*(check + 4)))
	{
		*(check + 4) = 1;
		return (0);
	}
	else if (!ft_strcmp("F", id) && (*(check + 4)))
		return (1);
	if (!ft_strcmp("C", id) && !(*(check + 5)))
	{
		*(check + 5) = 1;
		return (0);
	}
	else if (!ft_strcmp("C", id) && (*(check + 5)))
		return (1);
	return (1);
}

int	check_ids(int *check, char *id)
{
	if (!id || !ft_strcmp("\n", id))
		return (0);
	if (!ft_strcmp("NO", id) && !(*check))
	{
		*check = 1;
		return (0);
	}
	else if (!ft_strcmp("NO", id) && (*check))
		return (1);
	if (!ft_strcmp("WE", id) && !(*(check + 1)))
	{
		*(check + 1) = 1;
		return (0);
	}
	else if (!ft_strcmp("WE", id) && (*(check + 1)))
		return (1);
	if (!ft_strcmp("SO", id) && !(*(check + 2)))
	{
		*(check + 2) = 1;
		return (0);
	}
	else if (!ft_strcmp("SO", id) && (*(check + 2)))
		return (1);
	return (check_ids_2(check, id));
}

uint32_t	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

static int	condition_color_text(t_data_map	*map)
{
	return (map->c == 0 || map->f == 0 || !map->ea
		|| !map->no || !map->so || !map->we);
}

t_data_map	*load_map(char *filename)
{
	t_data_map	*map;
	t_any_vars	av;
	int			fd;

	if (checkfilename(filename))
		return (ft_printf("Error\nFile Format\n"), NULL);
	map = (t_data_map *)malloc(sizeof(t_data_map));
	if (!map)
		return (NULL);
	init_map(map);
	if (load_textures_map(filename, map))
		return (ft_printf("Error\nTextures\n"), free_map(map), NULL);
	if (load_colors_map(filename, map))
		return (ft_printf("Error\nColors\n"), free_map(map), NULL);
	if (condition_color_text(map))
		return (ft_printf("Error\nData Format\n"), free_map(map), NULL);
	av.ctrl = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	if (load_content_map(map, fd, &av))
		return (ft_printf("Error\nLoad Map\n"), free_map(map), NULL);
	if (check_valid_map(map))
		return (ft_printf("Error\nInvalid Map\n"), free_map(map), NULL);
	return (map);
}
