/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 11:47:26 by atalaver          #+#    #+#             */
/*   Updated: 2022/07/17 12:24:45 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdlib.h>

unsigned int	**ft_createmap(void)
{
	unsigned int	*p;
	unsigned int	**map;
	unsigned int	i;
	unsigned int	j;

	map = malloc(sizeof(unsigned int *) * 4);
	i = 0;
	while (i < 4)
	{
		p = malloc(sizeof(unsigned int) * 4);
		j = 1;
		while (j <= 4)
		{
			p[j - 1] = j;
			j++;
		}
		map[i] = p;
		i++;
	}
	return (map);
}

unsigned int	**ft_collectdata(char *str)
{
	unsigned int	*p;
	unsigned int	**data;
	unsigned int	i;
	unsigned int	j;
	unsigned int	l;

	data = malloc(sizeof(unsigned int *) * 4);
	i = 0;
	l = 0;
	while (i < 4)
	{
		p = malloc(sizeof(unsigned int) * 4);
		j = 1;
		while (j <= 4)
		{
			p[j - 1] = (str[l] - '0');
			l += 2;
			j++;
		}
		data[i] = p;
		i++;
	}
	return (data);
}

void	ft_free_memory(unsigned int **memory)
{
	unsigned int	i;

	i = 0;
	while (i < 4)
	{
		free(memory[i]);
		memory[i] = NULL;
		i++;
	}
	free(memory);
}
