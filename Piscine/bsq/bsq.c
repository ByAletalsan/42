/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 18:22:21 by asalas-s          #+#    #+#             */
/*   Updated: 2022/07/27 21:47:06 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"structs.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int		ft_check_map(char	*str);
void	ft_load(struct s_map *map_info, char *str);
void	ft_print_map(struct s_map map_info);
void	ft_free_memory(struct s_map *map_info);
void	ft_standard_input(void);
int		ft_fill_map(struct s_map *map_info);

void	ft_work(struct s_map *map_info, char *argv)
{
	ft_load(map_info, argv);
	if (ft_fill_map(map_info))
		ft_print_map(*map_info);
	else
		write(1, "map error\n", 10);
	ft_free_memory(map_info);
	return ;
}

int	main(int argc, char **argv)
{
	struct s_map	map_info;
	int				i;

	i = 1;
	if (argc < 2)
	{
		ft_standard_input();
		if (ft_check_map("stdinput.txt"))
			ft_work(&map_info, "stdinput.txt");
	}
	else
	{
		while (i < argc)
		{
			if (ft_check_map(argv[i]))
				ft_work(&map_info, argv[i]);
			if (i != (argc - 1))
				write(1, "\n", 1);
			i++;
		}
	}
	return (0);
}
