/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 19:50:53 by alumno            #+#    #+#             */
/*   Updated: 2022/09/22 12:02:22 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_words(char const *s, char c)
{
	size_t	i;
	size_t	n;
	size_t	v;

	i = 0;
	n = 0;
	v = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c && v > 0)
		{
			n++;
			v = 0;
		}
		if (s[i] != c)
			v++;
		i++;
	}
	if (v > 0)
		return (n + 1);
	else
		return (n);
}

static size_t	ft_strlenc(const char *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0' && s[i] != c)
		i++;
	return (i);
}

static char	*ft_crtwrd(const char *s, size_t len)
{
	size_t	i;
	char	*f;

	f = (char *)malloc(len + 1);
	if (!f)
		return (NULL);
	i = 0;
	while (i < len)
	{
		f[i] = s[i];
		i++;
	}
	f[i] = '\0';
	return (f);
}

char	**ft_split(char const *s, char c)
{
	char	**m;
	size_t	i;
	size_t	len;
	size_t	n_words;

	n_words = ft_count_words(s, c);
	m = (char **)malloc((n_words + 1) * sizeof(char *));
	if (!m)
		return (NULL);
	i = 0;
	while (i < n_words)
	{
		while (*s == c)
			s += 1;
		len = ft_strlenc(s, c);
		m[i] = ft_crtwrd(s, len);
		if (i != (n_words - 1))
			s += len + 1;
		i++;
	}
	m[i] = NULL;
	return (m);
}
