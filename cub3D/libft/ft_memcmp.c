/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvasco-m <dvasco-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 11:26:30 by dvasco-m          #+#    #+#             */
/*   Updated: 2022/09/28 21:32:00 by dvasco-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (*(unsigned char *)(s1 + i) == *(unsigned char *)(s2 + i))
		{
			i++;
		}
		else
		{
			return (*(unsigned char *)(s1 + i) - (*(unsigned char *)(s2 + i)));
		}
	}
	return (0);
}
