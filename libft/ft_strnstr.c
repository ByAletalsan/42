/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 11:47:44 by alumno            #+#    #+#             */
/*   Updated: 2022/09/23 18:46:40 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_str_cmp(const char *s1, const char *s2, size_t len, int i)
{
	int		n;
	size_t	j;

	j = 0;
	n = 0;
	while (s1[i + j] != '\0' && s1[i + j] == s2[j] && (i + j < len))
	{
		j++;
		n++;
	}
	if ((size_t)n == ft_strlen(s2))
		return (1);
	return (0);
}

char	*ft_strnstr(const char *s1, const char *s2, size_t len)
{
	size_t	i;

	i = 0;
	if (s2[0] == '\0')
		return ((char *)s1);
	if (s1[0] == '\0')
		return (NULL);
	if (ft_strlen(s1) < ft_strlen(s2) || len == 0)
		return (NULL);
	while (s1[i] != '\0' && i < len)
	{
		if (s1[i] == s2[0])
		{
			if (ft_str_cmp(s1, s2, len, i))
				return ((char *)&s1[i]);
		}
		i++;
	}
	return (NULL);
}
