/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 10:03:16 by atalaver          #+#    #+#             */
/*   Updated: 2022/09/23 18:41:28 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*matriz;

	matriz = (void *)malloc(size * nmemb);
	if (!matriz)
		return (NULL);
	ft_bzero(matriz, (size * nmemb));
	return (matriz);
}
