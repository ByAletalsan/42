/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 15:38:22 by atalaver          #+#    #+#             */
/*   Updated: 2022/09/23 17:08:23 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	char			*string_dst;
	const char		*string_src;

	i = 0;
	string_dst = dst;
	string_src = src;
	if (dst == 0 && src == 0)
		return (NULL);
	while (i < n)
	{
		*string_dst = *string_src;
		string_dst += 1;
		string_src += 1;
		i++;
	}
	return (dst);
}
