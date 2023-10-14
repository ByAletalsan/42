/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvasco-m <dvasco-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 21:36:35 by dvasco-m          #+#    #+#             */
/*   Updated: 2023/05/19 13:40:19 by dvasco-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char		*ptr;
	size_t		lens1;
	size_t		lens2;
	size_t		total_len;

	lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	total_len = lens1 + lens2;
	ptr = (char *)malloc((total_len + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	ptr[0] = '\0';
	ft_strlcat(ptr, s1, total_len + 1);
	ft_strlcat(ptr, s2, total_len + 1);
	return (ptr);
}
