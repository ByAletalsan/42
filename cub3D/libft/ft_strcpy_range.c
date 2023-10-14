/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy_range.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 19:35:06 by dvasco-m          #+#    #+#             */
/*   Updated: 2023/06/18 23:07:03 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strcpy_range(char *str, int i, int j)
{
	char	*copy;
	int		k;

	copy = malloc(j - i + 1);
	k = 0;
	while (i < j)
	{
		copy[k] = str[i];
		k++;
		i++;
	}
	copy[k] = '\0';
	return (copy);
}
