/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 10:12:21 by alumno            #+#    #+#             */
/*   Updated: 2022/09/22 10:22:51 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_rmchr(char *s, size_t i)
{
	size_t	len;

	len = ft_strlen(s);
	while (i < (len - 1))
	{
		s[i] = s[i + 1];
		i++;
	}
	s[i] = '\0';
}

static void	ft_trim(char *s, const char *set, size_t i)
{
	int		control;
	size_t	j;

	control = 1;
	while (control)
	{
		j = 0;
		control = 0;
		while (set[j] != '\0')
		{
			if (s[i] == set[j])
			{
				ft_rmchr(s, i);
				control = 1;
			}
			j++;
		}
		if (i > 0)
			i--;
	}
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*cp_s1;
	char	*f;
	size_t	len;

	cp_s1 = ft_strdup(s1);
	if (cp_s1)
	{
		ft_trim(cp_s1, set, 0);
		len = ft_strlen(cp_s1);
		ft_trim(cp_s1, set, (len - 1));
	}
	f = ft_strdup(cp_s1);
	free(cp_s1);
	return (f);
}
