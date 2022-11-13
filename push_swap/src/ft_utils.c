/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 08:32:53 by atalaver          #+#    #+#             */
/*   Updated: 2022/11/13 16:50:49 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

long	ft_atol(char *str)
{
	int		i;
	long	number;
	int		signo;

	i = 0;
	number = 0;
	signo = 1;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{	
		if (str[i] == '-')
			signo *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		number *= 10;
		number += str[i] - '0';
		i++;
	}
	return (number * signo);
}

static int	ft_cont_num(int len, char **argv)
{
	int		i;
	int		j;
	char	**s;
	int		l;

	i = 1;
	l = 0;
	while (i < len)
	{
		j = 0;
		s = ft_split((const char *)argv[i], ' ');
		while (s[j] != NULL)
		{
			l++;
			j++;
		}
		ft_free_split(s);
		i++;
	}
	return (l);
}

int	ft_find_indice(t_pila *a, int n)
{
	int	i;

	i = 0;
	while (i < a->len)
	{
		if (a->p[i] == n)
			return (i);
		i++;
	}
	return (-1);
}

int	ft_find_low_of_top(t_pila *a, int n)
{
	int	i;
	int	j;
	int	low;

	j = 0;
	while (a->p[j] < n)
		j++;
	if (j == a->len)
		return (a->len - 1);
	low = a->p[j];
	i = j;
	while (j < a->len)
	{
		if (a->p[j] < low && a->p[j] > n)
		{
			low = a->p[j];
			i = j;
		}
		j++;
	}
	return (ft_return_find_low_of_top(a, n, i));
}

t_pila	*ft_fill(int len, char **argv, char c)
{
	int		i;
	int		j;
	int		w;
	char	**s;
	t_pila	*p;

	p = (t_pila *)malloc(sizeof(t_pila));
	if (!p)
		return (NULL);
	p->len = ft_cont_num(len, argv);
	p->p = ft_calloc(p->len, sizeof(int));
	i = 1;
	w = 0;
	while (i < len)
	{
		j = 0;
		s = ft_split((const char *)argv[i], ' ');
		while (s[j] != NULL)
			p->p[w++] = ft_atoi(s[j++]);
		ft_free_split(s);
		i++;
	}
	p->c = c;
	return (p);
}
