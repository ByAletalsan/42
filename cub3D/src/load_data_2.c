/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_data_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 19:29:21 by dvasco-m          #+#    #+#             */
/*   Updated: 2023/10/06 15:04:14 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static int	evaluate_checks(t_any_vars	*av)
{
	return (!(av->check)[0] || !(av->check)[1] || !(av->check)[2] ||
			!(av->check)[3] || !(av->check)[4] ||!(av->check)[5]);
}

static int	analize_line(t_any_vars *av, char **line,
			t_list **list, char **split)
{
	split = ft_split(*line, ' ');
	if (!split)
		return (free(*line), 1);
	if (evaluate_checks(av))
	{
		if (check_ids(av->check, split[0]))
			return (ft_free_params(split), free(*line), 1);
	}
	else
	{
		if (av->ctrl == 2 && split[0] && ft_strcmp("\n", split[0]))
			return (ft_lstclear(list, free_content_lst),
				ft_free_params(split), free(*line), 1);
		if (split[0] && ft_strcmp("\n", split[0]))
		{
			av->ctrl = 1;
			if (!list)
				*list = ft_lstnew(ft_strtrim(*line, "\n"));
			else
				ft_lstadd_back(list, ft_lstnew(ft_strtrim(*line, "\n")));
		}
		else if (av->ctrl == 1)
			av->ctrl = 2;
	}
	return (ft_free_params(split), 0);
}

int	load_content_map(t_data_map *map, int fd, t_any_vars *av)
{
	char	*line;
	t_list	*list;

	list = NULL;
	av->check = (int *)ft_calloc(6, sizeof(int));
	if (!(av->check))
		return (close(fd), 1);
	line = get_next_line_ale(fd);
	while (line)
	{
		if (analize_line(av, &line, &list, NULL))
			return (close(fd), free(av->check), 1);
		free(line);
		line = get_next_line_ale(fd);
	}
	if (line)
		free(line);
	map->map = list_to_matrix(list);
	ft_lstclear(&list, free_content_lst);
	if (!map->map)
		return (free(av->check), close(fd), 1);
	return (free(av->check), close(fd), 0);
}

void	free_map(t_data_map *map)
{
	if (map->ea)
		free(map->ea);
	if (map->no)
		free(map->no);
	if (map->so)
		free(map->so);
	if (map->we)
		free(map->we);
	if (map->map)
		ft_free_params(map->map);
	if (map)
		free(map);
}

int	checkfilename(char *filename)
{
	char	**split;
	int		len_split;

	split = ft_split(filename, '.');
	if (!split)
		return (1);
	len_split = ft_len_matrix2(split);
	if (len_split < 2)
		return (ft_free_params(split), 1);
	if (ft_strcmp(split[len_split - 1], "cub") != 0)
		return (ft_free_params(split), 1);
	else
		return (ft_free_params(split), 0);
}
