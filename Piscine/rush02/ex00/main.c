/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 12:25:39 by atalaver          #+#    #+#             */
/*   Updated: 2022/07/17 13:11:01 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<unistd.h>
#include<stdio.h>

unsigned int	**ft_createmap(void);
unsigned int	**ft_collectdata(char *str);
int				ft_control_err(int argc, char *str);
void			ft_printmap(unsigned int **map);
int				ft_comb(unsigned int **map, int m, unsigned int **condition);
void			ft_free_memory(unsigned int **memory);

int	main(int argc, char **argv)
{
	unsigned int	**map;
	unsigned int	**condition;

	if (ft_control_err(argc, argv[1]) > 0)
		return (1);
	map = ft_createmap();
	condition = ft_collectdata(argv[1]);
	if (ft_comb(map, 3, condition) == 0)
	{
		write(1, "Error\n", 6);
	}
	else
		ft_printmap(map);
	ft_free_memory(map);
	ft_free_memory(condition);
	return (0);
}
