/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alumno <alumno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 09:44:15 by alumno            #+#    #+#             */
/*   Updated: 2022/09/20 10:09:47 by alumno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*memmove(void *dest, void *src, size_t n)
{
	size_t			i;
	char			*string_dst;
	const char		*string_src;

	i = 0;
	string_dst = dest;
	string_src = src;
	if (dest == 0 || src == 0)
		return (NULL);
	while (i < n)
	{
		*string_dst = *string_src;
		string_dst += 1;
		string_src += 1;
		i++;
	}
	return (dest);
}
