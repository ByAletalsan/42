/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 11:14:20 by alumno            #+#    #+#             */
/*   Updated: 2022/09/23 18:57:24 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t		i;
	const char	*p;

	i = 0;
	p = s;
	while (i < n)
	{
		if (p[i] == (char)c)
			return ((void *)&p[i]);
		i++;
	}
	return (NULL);
}
