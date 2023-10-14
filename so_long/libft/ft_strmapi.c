/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alumno <alumno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 09:44:04 by alumno            #+#    #+#             */
/*   Updated: 2022/09/22 09:48:50 by alumno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*p;
	size_t	i;

	i = 0;
	p = ft_strdup(s);
	if (p)
	{
		while (p[i] != '\0')
		{
			p[i] = f(i, p[i]);
			i++;
		}
	}
	return (p);
}
