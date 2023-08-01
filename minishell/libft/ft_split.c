/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvasco-m <dvasco-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 14:52:33 by dvasco-m          #+#    #+#             */
/*   Updated: 2023/03/21 20:42:28 by dvasco-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

typedef struct s_param
{
	size_t		w;
	size_t		first;
	size_t		words;
	char const	*s;
}t_param;

static	size_t	count_words(char const *s, char c)
{
	size_t	i;
	size_t	w;
	size_t	first;

	w = 0;
	i = 0;
	first = 1;
	while (s[i] != '\0')
	{
		if (s[i] == c)
		{
			first = 1;
		}
		if (s[i] != c && first == 1)
		{
			w += 1;
			first = 0;
		}
		i++;
	}
	return (w);
}

static	size_t	size_of_word(const char *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] != c && s[i] != '\0')
		i++;
	return (i);
}

static	char	**ft_free(char **array_ptr, size_t w)
{
	size_t	i;

	i = 0;
	while (i < w)
	{
		free (array_ptr[i]);
		i++;
	}
	free(array_ptr);
	return (NULL);
}

static	char	**make_split(char **array_ptr, size_t *i, t_param *p, char c)
{
	while (p->w < p->words && *(p->s + *i) != '\0')
	{
		if (*(p->s + *i) == c)
		{
			p->first = 1;
			*i = *i + 1;
		}
		if (*(p->s + *i) != c && p->first == 1)
		{
			array_ptr[p->w] = ft_substr(p->s, *i, size_of_word((p->s + *i), c));
			if (array_ptr[p->w] == NULL)
				return (ft_free(array_ptr, p->w));
			p->w += 1;
			p->first = 0;
		}
		*i = *i + 1;
	}
	array_ptr[p->w] = NULL;
	return (array_ptr);
}

char	**ft_split(char const *s, char c)
{
	t_param	p;
	size_t	i;
	char	**array_ptr;

	p.words = count_words(s, c);
	p.s = s;
	array_ptr = (char **)malloc((p.words + 1) * sizeof(char *));
	if (array_ptr == NULL)
		return (NULL);
	i = 0;
	p.first = 1;
	p.w = 0;
	array_ptr = make_split(array_ptr, &i, &p, c);
	return (array_ptr);
}
