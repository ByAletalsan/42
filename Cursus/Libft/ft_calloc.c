/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alumno <alumno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 12:11:42 by alumno            #+#    #+#             */
/*   Updated: 2022/09/20 12:17:51 by alumno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*matriz;
	size_t	i;

	matriz = (void *)malloc(size * nmemb);
	i = 0;
	while (i < nmemb)
	{
		((char *)matriz)[i] = 0;
		i++;
	}
	return matriz;
}
