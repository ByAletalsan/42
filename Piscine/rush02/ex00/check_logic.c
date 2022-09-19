/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_logic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 12:32:19 by atalaver          #+#    #+#             */
/*   Updated: 2022/07/17 13:00:19 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_ck_colup(unsigned int **map, unsigned int **condition);
int	ft_ck_coldown(unsigned int **map, unsigned int **condition);
int	ft_ck_rowleft(unsigned int **map, unsigned int **condition);
int	ft_ck_rowright(unsigned int **map, unsigned int **condition);

int	ft_check_rep(unsigned int **map)
{
	int				count;
	unsigned int	i;
	unsigned int	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		count = 0;
		while (j < 4)
		{
			count += map[j][i];
			j++;
		}
		if (count != 10)
			return (0);
		i++;
	}
	return (1);
}

int	ft_check_comb(unsigned int **map, unsigned int **condition)
{
	if (ft_ck_colup(map, condition) && ft_ck_coldown(map, condition))
	{
		if (ft_ck_rowleft(map, condition) && ft_ck_rowright(map, condition))
		{
			if (ft_check_rep(map))
				return (1);
		}
	}
	return (0);
}
