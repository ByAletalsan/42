/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 10:03:16 by atalaver          #+#    #+#             */
/*   Updated: 2022/09/22 10:03:18 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*matriz;
	size_t	i;

	matriz = (void *)malloc(size * nmemb);
	if (!matriz)
		return (NULL);
	i = 0;
	while (i < nmemb)
	{
		((char *)matriz)[i] = 0;
		i++;
	}
	return (matriz);
}
