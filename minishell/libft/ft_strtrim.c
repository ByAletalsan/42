/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvasco-m <dvasco-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 21:55:29 by dvasco-m          #+#    #+#             */
/*   Updated: 2022/09/30 18:42:00 by dvasco-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t	is_in_the_set(const char *set, char c)
{
	size_t	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t		l_off;
	size_t		r_off;
	char		*ptr;
	size_t		i;

	l_off = 0;
	while (s1[l_off] != '\0' && is_in_the_set(set, s1[l_off]))
		l_off++;
	r_off = ft_strlen(s1);
	while (r_off > l_off && is_in_the_set(set, s1[r_off - 1]))
		r_off--;
	ptr = (char *)malloc((r_off - l_off + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (l_off < r_off)
	{
		ptr[i] = s1[l_off];
		i++;
		l_off++;
	}
	ptr[i] = '\0';
	return (ptr);
}
