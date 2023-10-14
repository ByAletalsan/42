/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvasco-m <dvasco-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 19:12:31 by dvasco-m          #+#    #+#             */
/*   Updated: 2022/09/28 21:32:13 by dvasco-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		c;
	size_t		i;

	if (dest > src)
	{
		while (n > 0)
		{
			c = *(char *)(src + n - 1);
			*(char *)(dest + n - 1) = c;
			n--;
		}
	}
	else if (dest < src)
	{	
		i = 0;
		while (i < n)
		{
			c = *(char *)(src + i);
			*(char *)(dest + i) = c;
			i++;
		}
	}
	return (dest);
}
