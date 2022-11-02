/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 08:32:53 by atalaver          #+#    #+#             */
/*   Updated: 2022/11/02 11:46:00 by atalaver         ###   ########.fr       */
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

t_pila	*ft_fill(int len, char **argv)
{
	int		i;
	t_pila	*p;

	i = 0;
	p = (t_pila *)malloc(sizeof(t_pila));
	if (!p)
		return (NULL);
	p->p = ft_calloc(len, sizeof(int));
	p->len = len - 1;
	while (i < p->len)
	{
		p->p[i] = ft_atoi(argv[i + 1]);
		i++;
	}
	return (p);
}
