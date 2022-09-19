/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 13:27:07 by atalaver          #+#    #+#             */
/*   Updated: 2022/07/17 13:04:53 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<unistd.h>

int	ft_check_comb(unsigned int **map, unsigned int **condition);

void	ft_printmap(unsigned int **map)
{
	unsigned int	i;
	unsigned int	j;
	unsigned char	c;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			c = map[i][j] + '0';
			write(1, &c, 1);
			if (j != 3)
				write(1, " ", 1);
			j++;
		}
		write(1, "\n", 1);
		i++;
	}
	return ;
}

void	ft_put_start_comb(unsigned int **map, int m, int n_start)
{
	unsigned int	i;

	i = 0;
	while (i < 4)
	{
		map[m][i] = n_start;
		n_start += 1;
		if (n_start > 4)
			n_start = 1;
		i++;
	}
	return ;
}

void	ft_swap(unsigned int **map, unsigned int *j, unsigned int m)
{
	unsigned int	aux;

	aux = map[m][*j];
	map[m][*j] = map[m][*j + 1];
	map[m][*j + 1] = aux;
	*j += 1;
	if (*j > 2)
		*j = 1;
	return ;
}

int	ft_comb(unsigned int **map, int m, unsigned int **condition)
{
	unsigned int	j;
	unsigned int	count;
	unsigned int	i;

	count = 0;
	while (++count <= 4)
	{
		ft_put_start_comb(map, m, count);
		i = 0;
		j = 1;
		while (i++ < 6)
		{
			if (m > 0)
			{
				if (ft_comb(map, m - 1, condition) == 1)
					return (1);
			}
			if (ft_check_comb(map, condition))
				return (1);
			ft_swap(map, &j, m);
		}
	}
	if (m == 3)
		return (0);
	return (2);
}
