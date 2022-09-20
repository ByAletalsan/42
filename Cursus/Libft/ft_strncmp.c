/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alumno <alumno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 11:05:17 by alumno            #+#    #+#             */
/*   Updated: 2022/09/20 11:07:36 by alumno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;
	int				res;

	i = 0;
	res = 0;
	if (n == 0)
		return (0);
	while (!res && (s1[i] != '\0' || s2[i] != '\0') && i < n)
	{
		res = s1[i] - s2[i];
		if (!res)
			i++;
	}
	if (i < n)
	{
		res = s1[i] - s2[i];
	}
	return (res);
}
