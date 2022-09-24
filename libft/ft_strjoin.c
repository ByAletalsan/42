/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alumno <alumno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 10:05:21 by alumno            #+#    #+#             */
/*   Updated: 2022/09/21 10:09:39 by alumno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*r;
	size_t	i;
	size_t	j;

	r = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	i = 0;
	j = 0;
	if (!r)
		return (NULL);
	while (s1[i] != '\0')
	{
		r[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		r[i] = s2[j];
		j++;
		i++;
	}
	r[i] = '\0';
	return (r);
}
