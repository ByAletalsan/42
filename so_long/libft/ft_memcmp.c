/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 11:28:33 by alumno            #+#    #+#             */
/*   Updated: 2022/09/23 17:13:54 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	int			i;
	int			res;
	const char	*p1;
	const char	*p2;

	i = 0;
	res = 0;
	p1 = s1;
	p2 = s2;
	if (n == 0)
		return (0);
	while (!res && i < (int)n)
	{
		res = (unsigned char)p1[i] - (unsigned char)p2[i];
		if (!res)
			i++;
	}
	if (i < (int)n)
	{
		res = (unsigned char)p1[i] - (unsigned char)p2[i];
	}
	return (res);
}
