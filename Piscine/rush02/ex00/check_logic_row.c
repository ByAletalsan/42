/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_logic_row.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 12:54:27 by atalaver          #+#    #+#             */
/*   Updated: 2022/07/17 12:54:44 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_ck_rowleft(unsigned int **map, unsigned int **condition)
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
			if (map[j][i] > top_number)
			{
				top_number = map[j][i];
				count_top_number++;
			}
			i++;
		}
		if (count_top_number != condition[2][j])
			return (0);
		j++;
	}
	return (1);
}

int	ft_ck_rowright(unsigned int **map, unsigned int **condition)
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
			if (map[j][(unsigned int)i] > top_number)
			{
				top_number = map[j][(unsigned int)i];
				count_top_number++;
			}
			i--;
		}
		if (count_top_number != condition[3][j])
			return (0);
		j++;
	}
	return (1);
}
