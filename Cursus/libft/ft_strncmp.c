/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 11:05:17 by alumno            #+#    #+#             */
/*   Updated: 2022/09/22 11:38:06 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	if (n == 0)
		return (0);
	while (!res && (s1[i] != '\0' || s2[i] != '\0') && i < (int)n)
	{
		res = (unsigned char)s1[i] - (unsigned char)s2[i];
		if (!res)
			i++;
	}
	if (i < (int)n)
	{
		res = (unsigned char)s1[i] - (unsigned char)s2[i];
	}
	return (res);
}
