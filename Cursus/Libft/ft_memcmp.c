/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alumno <alumno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 11:28:33 by alumno            #+#    #+#             */
/*   Updated: 2022/09/20 11:34:51 by alumno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t		i;
	int			res;
	const char	*p1;
	const char	*p2;

	i = 0;
	res = 0;
	p1 = s1;
	p2 = s2;
	if (n == 0)
		return (0);
	while (!res && (p1[i] != '\0' || p2[i] != '\0') && i < n)
	{
		res = p1[i] - p2[i];
		if (!res)
			i++;
	}
	if (i < n)
	{
		res = p1[i] - p2[i];
	}
	return (res);
}
