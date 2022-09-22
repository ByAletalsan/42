/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 09:39:58 by alumno            #+#    #+#             */
/*   Updated: 2022/09/22 11:48:53 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*p;
	int		i;

	i = 0;
	p = (char *)malloc(len + 1);
	if (!p)
		return (NULL);
	while ((s + start)[i] != '\0' && i < (int)len)
	{
		p[i] = (s + start)[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}
