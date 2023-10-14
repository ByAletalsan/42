/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_m2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 14:52:33 by dvasco-m          #+#    #+#             */
/*   Updated: 2023/06/28 17:53:56 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_word(char *s, int *q, char c)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	q = (int *)ft_calloc(2, sizeof(int));
	if (q == NULL)
		return (0);
	while (s[i] == c)
		i++;
	if (s[i] == '\'' || s[i] == '"')
	{
		quotes(s[i++], q);
		len++;
	}
	while (s[i] && (s[i] != c || q[1]))
	{
		quotes(s[i], q);
		len++;
		i++;
	}
	return (free(q), len);
}

static int	init(int **q, char **word, int len)
{
	*word = (char *)ft_calloc(len + 1, 1);
	if (!(*word))
		return (1);
	*q = (int *)ft_calloc(2, sizeof(int));
	if (*q == NULL)
		return (free(word), 1);
	return (0);
}

static char	*ft_word(char *s, int *j, int *q, char c)
{
	char	*word;
	int		i;
	int		k;

	i = 0;
	k = 0;
	if (init(&q, &word, ft_count_word(s, q, c)) == 1)
		return (NULL);
	while (s[i] == c)
		i++;
	if (s[i] == '\'' || s[i] == '"')
	{
		quotes(s[i], q);
		word[k++] = s[i++];
	}
	while (s[i] && (s[i] != c || q[1]))
	{
		quotes(s[i], q);
		word[k++] = s[i++];
	}
	*j += i;
	return (free(q), word);
}

static int	ft_count_words(char *s, char c, int i, int *q)
{
	int	control;
	int	n_words;

	control = 0;
	n_words = 0;
	q = (int *)ft_calloc(2, sizeof(int));
	if (q == NULL)
		return (0);
	while (s[++i])
	{
		if (s[i] == c && (control && !q[1]))
		{
			n_words++;
			control = 0;
		}
		else
		{
			control = 1;
			quotes(s[i], q);
		}
	}
	if (control)
		n_words++;
	return (free(q), n_words);
}

char	**ft_split_m2(char *s, char c)
{
	char	**words;
	int		n_words;
	int		i;
	int		j;
	int		*q;

	if (!s)
		return (NULL);
	q = NULL;
	n_words = ft_count_words(s, c, -1, q);
	words = (char **)ft_calloc(n_words + 1, sizeof(char *));
	if (!words)
		return (NULL);
	i = 0;
	j = 0;
	while (i < n_words)
	{
		words[i] = ft_word(s + j, &j, q, c);
		if (!words[i++])
			return (ft_free_params(words), NULL);
	}
	return (words);
}
