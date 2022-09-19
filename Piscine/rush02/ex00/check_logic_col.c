/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_logic_col.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 19:16:54 by atalaver          #+#    #+#             */
/*   Updated: 2022/07/17 12:52:47 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_ck_colup(unsigned int **map, unsigned int **condition)
{
	unsigned int	top_number;
	unsigned int	count_top_number;
	unsigned int	i;
	unsigned int	j;

	j = 0;
	while (j < 4)
	{
		i = 0;
		top_number = 0;
		count_top_number = 0;
		while (i < 4)
		{
			if (map[i][j] > top_number)
			{
				top_number = map[i][j];
				count_top_number++;
			}
			i++;
		}
		if (count_top_number != condition[0][j])
			return (0);
		j++;
	}
	return (1);
}

int	ft_ck_coldown(unsigned int **map, unsigned int **condition)
{
	unsigned int	top_number;
	unsigned int	count_top_number;
	int				i;
	unsigned int	j;

	j = 0;
	while (j < 4)
	{
		i = 3;
		count_top_number = 0;
		top_number = 0;
		while (i >= 0)
		{
			if (map[(unsigned int)i][j] > top_number)
			{
			top_number = map[(unsigned int)i][j];
			count_top_number++;
			}
			i--;
		}
		if (count_top_number != condition[1][j])
			return (0);
		j++;
	}
	return (1);
}
