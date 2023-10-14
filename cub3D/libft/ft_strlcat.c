/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvasco-m <dvasco-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 08:57:53 by dvasco-m          #+#    #+#             */
/*   Updated: 2022/09/30 18:41:32 by dvasco-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	len_s;
	size_t	len_d;

	len_d = ft_strlen(dst);
	len_s = ft_strlen(src);
	i = len_d;
	j = 0;
	if (len_d < dstsize - 1 && dstsize > 0)
	{
		while (src[j] != '\0' && len_d + j < dstsize - 1)
		{
			dst[i] = src[j];
			i++;
			j++;
		}
		dst[i] = '\0';
	}
	if (len_d >= dstsize)
		len_d = dstsize;
	return (len_d + len_s);
}
