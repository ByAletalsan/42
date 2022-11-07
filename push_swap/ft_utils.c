/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 08:32:53 by atalaver          #+#    #+#             */
/*   Updated: 2022/11/07 13:41:27 by atalaver         ###   ########.fr       */
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
		free(s);
		i++;
	}
	return (l);
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
		free(s);
		i++;
	}
	p->c = c;
	return (p);
}
