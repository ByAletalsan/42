/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 19:50:53 by alumno            #+#    #+#             */
/*   Updated: 2022/09/23 19:57:48 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(char const *s, char c)
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

static int	ft_strlenc(char const *s2, char c, int i)
{
	int	len;

	len = 0;
	while (s2[i] != c && s2[i] != '\0')
	{
		len++;
		i++;
	}
	return (len);
}

static char	**ft_free_matriz(char **matriz, int i)
{
	while (i > 0)
	{
		i--;
		free(matriz[i]);
	}
	free(matriz);
	return (NULL);
}

static char	**ft_create_matriz(char const *s, char **matriz, char c, int words)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	while (s[i] != '\0' && j < words)
	{
		k = 0;
		while (s[i] == c)
			i++;
		matriz[j] = (char *)malloc(ft_strlenc(s, c, i) + 1);
		if (!matriz[j])
			return (ft_free_matriz(matriz, j));
		while (s[i] != '\0' && s[i] != c)
			matriz[j][k++] = s[i++];
		matriz[j][k] = '\0';
		j++;
	}
	matriz[j] = 0;
	return (matriz);
}

char	**ft_split(char const *s, char c)
{
	char	**matriz;
	int		words;

	if (!s)
		return (NULL);
	words = ft_count_words(s, c);
	matriz = (char **)malloc(sizeof(char *) * (words + 1));
	if (!matriz)
		return (NULL);
	return (ft_create_matriz(s, matriz, c, words));
}
