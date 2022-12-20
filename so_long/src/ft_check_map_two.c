/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_map_two.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 12:14:57 by atalaver          #+#    #+#             */
/*   Updated: 2022/12/20 19:24:35 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	ft_check_limit(t_mapa map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map.height)
	{
		j = 0;
		while (j < map.width)
		{
			if (i == 0 && map.mapa[j] != '1')
				return (1);
			else if (i == map.height - 1
				&& map.mapa[(i * (map.width + 1)) + j] != '1')
				return (1);
			else if ((j == 0 || j == map.width - 1)
				&& map.mapa[(i * (map.width + 1)) + j] != '1')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
