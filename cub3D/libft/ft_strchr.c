/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvasco-m <dvasco-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 10:27:10 by dvasco-m          #+#    #+#             */
/*   Updated: 2022/09/30 18:41:14 by dvasco-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char		*ptr;
	size_t		i;
	size_t		len;
	int			found;

	ptr = 0;
	len = ft_strlen(s);
	i = 0;
	found = 0;
	while (i <= len && !found)
	{
		if (s[i] == (char)c)
		{
			ptr = (char *)s + i;
			found = 1;
		}
		i++;
	}
	return (ptr);
}
