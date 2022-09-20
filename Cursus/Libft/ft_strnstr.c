/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alumno <alumno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 11:47:44 by alumno            #+#    #+#             */
/*   Updated: 2022/09/20 12:03:39 by alumno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_strnstr(const char *s1, const char *s2, size_t len)
{
	size_t	i;
	size_t	j;
	int 	n;

	i = 0;
	if (len == 0)
		return ((char *)s1);
	if (!s1)
		return ((char *)s2);
	if (!s2)
		return ((char *)s1);
	if (ft_strlen(s1) < ft_strlen(s2))
		return (NULL);
	while (s1[i] != '\0' && i < len)
	{
		if (s1[i] == s2[0])
		{
			j = 0;
			n = 0;
			while (s1[i + j] != '\0' && s1[i + j] == s2[j] && (i + j < len))
			{
				j++;
				n++;
			}
			if (n == ft_strlen(s2))
				return ((char *)&s1[i]);
		}
		i++;
	}
	return (NULL);
}
