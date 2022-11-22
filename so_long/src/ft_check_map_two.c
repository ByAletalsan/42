/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_map_two.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 12:14:57 by atalaver          #+#    #+#             */
/*   Updated: 2022/11/22 12:28:18 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	ft_check_limit(const char *s)
{
	int	i;
	int	row;

	i = 0;
	row = 0;
	while (s[i] != '\0')
	{
		if (row == 0 && s[i] != '1' && s[i] != '\n')
			return (1);
		if (s[i] == '\n')
		{
			row++;
			if (s[i + 1] != '1' || s[i - 1] != '1')
				return (1);
		}
		i++;
	}
	i--;
	while (s[i] != '\n')
	{
		if (s[i] != '1')
			return (1);
		i--;
	}
	return (0);
}
