/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvasco-m <dvasco-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 11:08:51 by dvasco-m          #+#    #+#             */
/*   Updated: 2022/09/28 22:27:16 by dvasco-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t		i;
	int			found;
	void		*ptr;

	i = 0;
	found = 0;
	ptr = 0;
	while (i < n && !found)
	{
		if ((unsigned char)c == *(unsigned char *)(s + i))
		{
			ptr = (void *)s + i;
			found = 1;
		}
		i++;
	}
	return (ptr);
}
