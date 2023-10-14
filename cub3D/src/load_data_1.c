/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_data_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 19:26:50 by dvasco-m          #+#    #+#             */
/*   Updated: 2023/09/29 18:07:47 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static char	*load_textures_rutes_map(char *line, char *id)
{
	char	*ptr;
	char	*ptr2;
	char	*aux;

	ptr = line;
	while (*ptr == ' ')
		ptr += 1;
	if (ft_strncmp(ptr, id, 3))
		return (NULL);
	ptr += 3;
	if (*ptr && *ptr != '\n')
	{
		while (*ptr == ' ' && *ptr != '\n' && *ptr)
			ptr += 1;
		ptr2 = ptr;
		while (*ptr2 != ' ' && *ptr2 != '\n' && *ptr2)
			ptr2 += 1;
		aux = ptr2;
		while (*aux == ' ' && *ptr2 != '\n' && *ptr2)
			aux += 1;
		if (!(*aux == '\n' || !(*aux)))
			return (NULL);
		return (ft_substr(ptr, 0, ptr2 - ptr));
	}
	return (NULL);
}

int	load_textures_map(char *filename, t_data_map *map)
{
	char	*line;
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (1);
	line = get_next_line(fd);
	while (line && (!map->no || !map->so || !map->we || !map->ea))
	{
		if (!map->no)
			map->no = load_textures_rutes_map(line, "NO ");
		if (!map->we)
			map->we = load_textures_rutes_map(line, "WE ");
		if (!map->so)
			map->so = load_textures_rutes_map(line, "SO ");
		if (!map->ea)
			map->ea = load_textures_rutes_map(line, "EA ");
		free(line);
		line = get_next_line(fd);
	}
	if (line)
		free(line);
	close(fd);
	return (0);
}

static uint32_t	set_color_map_2(char **numbers)
{
	int		i;
	char	**aux;
	char	*aux_char;
	int		n[3];

	i = -1;
	while (++i < 3)
	{
		aux_char = ft_strtrim(numbers[i], "\n");
		aux = ft_split(aux_char, ' ');
		free(aux_char);
		if (!aux)
			return (ft_free_params(numbers), 0);
		if (ft_len_matrix2(aux) != 1 || !ft_is_full_digit(aux[0]))
			return (ft_free_params(numbers), ft_free_params(aux), 0);
		n[i] = ft_atoi(aux[0]);
		if (n[i] < 0 || n[i] > 255)
			return (ft_free_params(numbers), ft_free_params(aux), 0);
		ft_free_params(aux);
	}
	return (ft_free_params(numbers), get_rgba(n[0], n[1], n[2], 255));
}

static uint32_t	set_color_map(char *line, char *id)
{
	char			*ptr;
	char			**numbers;

	ptr = line;
	while (*ptr == ' ')
		ptr += 1;
	if (ft_strncmp(ptr, id, 2))
		return (0);
	ptr += 2;
	if (ptr && *ptr)
	{
		numbers = ft_split(ptr, ',');
		if (!numbers)
			return (0);
		if (ft_len_matrix2(numbers) != 3)
			return (ft_free_params(numbers), 0);
		return (set_color_map_2(numbers));
	}
	return (0);
}

int	load_colors_map(char *filename, t_data_map *map)
{
	char	*line;
	int		fd;

	fd = open(filename, O_RDONLY | O_NONBLOCK);
	if (fd < 0)
		return (1);
	line = get_next_line_ale(fd);
	while (line)
	{
		if (!map->f)
			map->f = set_color_map(line, "F ");
		if (!map->c)
			map->c = set_color_map(line, "C ");
		free(line);
		line = get_next_line_ale(fd);
	}
	if (line)
		free(line);
	return (close(fd), 0);
}
