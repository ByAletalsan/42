/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 09:10:48 by atalaver          #+#    #+#             */
/*   Updated: 2022/10/20 20:16:08 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

//Bzero y calloc para hacer las reservas de memoria
static void	ft_bzero(void *s, int n)
{
	int		i;
	char	*p;

	i = 0;
	p = s;
	while (i < n)
	{
		*p = 0;
		i++;
		p += 1;
	}
	return ;
}

void	*ft_calloc(int nmemb, int size)
{
	void	*matriz;

	matriz = (void *)malloc(size * nmemb);
	if (!matriz)
		return (NULL);
	ft_bzero(matriz, (size * nmemb));
	return (matriz);
}

//Funciones para los strings
int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*r;
	int		i;
	int		j;

	r = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!r || !s1 || !s2)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i] != '\0')
	{
		r[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
		r[i++] = s2[j++];
	r[i] = '\0';
	return (r);
}

int	ft_chr_exist(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return (1);
		i++;
	}
	return (0);
}
