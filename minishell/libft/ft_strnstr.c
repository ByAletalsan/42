/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvasco-m <dvasco-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 12:45:03 by dvasco-m          #+#    #+#             */
/*   Updated: 2023/02/28 11:51:08 by dvasco-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t			i;
	size_t			j;
	size_t			match;

	i = 0;
	if (needle[i] == '\0')
		return ((char *)haystack);
	if (ft_strlen(needle) > ft_strlen(haystack) || len < ft_strlen(needle))
		return (0);
	while (i < len && haystack[i] != '\0' && (len - i) >= ft_strlen(needle))
	{
		match = 1;
		j = 0;
		while (j < ft_strlen(needle) && match)
		{
			if (haystack[i + j] != needle[j])
				match = 0;
			j++;
		}
		if (j == ft_strlen(needle) && match)
			return ((char *)haystack + i);
		i++;
	}
	return (0);
}
