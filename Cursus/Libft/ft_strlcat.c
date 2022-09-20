/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alumno <alumno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 10:36:51 by alumno            #+#    #+#             */
/*   Updated: 2022/09/20 10:40:12 by alumno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	size_src;
	size_t	size_dest;

	i = 0;
	j = 0;
	size_src = ft_strlen(src);
	size_dest = ft_strlen(dest);
	while (dest[i] > 0 && i < size)
		i++;
	while (i < size - 1 && size != 0 && src[j] > 0)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (size <= size_dest)
		return (size_src + size);
	else
	{
		dest[i] = '\0';
		return (size_dest + size_src);
	}
}
