/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_two.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 12:53:25 by atalaver          #+#    #+#             */
/*   Updated: 2022/11/08 17:12:09 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

int	ft_return_find_low_of_top(t_pila *a, int n, int i)
{
	int	j;
	int	n_low;

	j = 0;
	n_low = n;
	while (j < a->len)
	{
		if (a->p[j] > n_low)
			n_low = a->p[j];
		j++;
	}
	if (n_low == n)
		return (ft_find_indice(a, ft_find_low(a)));
	if (i >= a->len)
		return (0);
	else
		return (i);
}

void	ft_rev_rotate_both(t_pila *a, t_pila *b)
{
	int	aux;
	int	i;

	i = a->len - 1;
	aux = a->p[i];
	while (i > 0)
	{
		a->p[i] = a->p[i - 1];
		i--;
	}
	a->p[0] = aux;
	i = b->len - 1;
	aux = b->p[i];
	while (i > 0)
	{
		b->p[i] = b->p[i - 1];
		i--;
	}
	b->p[0] = aux;
	ft_printf("rrr\n");
}

t_cost	*ft_ini_cost(void)
{
	t_cost	*p;

	p = (t_cost *)malloc(sizeof(t_cost));
	if (!p)
		return (NULL);
	p->ra = 0;
	p->rb = 0;
	p->rr = 0;
	p->rra = 0;
	p->rrb = 0;
	p->rrr = 0;
	p->total = 0;
	return (p);
}

void	ft_cost(t_pila *a, t_pila *b, int i, t_cost *p)
{
	int		j;

	p->rb = ft_n_rotate(b, b->p[i]);
	p->rrb = ft_n_rev_rotate(b, b->p[i]);
	if (p->rb && p->rrb)
		p->rrb = 0;
	j = ft_find_low_of_top(a, b->p[i]);
	p->ra = ft_n_rotate(a, a->p[j]);
	p->rra = ft_n_rev_rotate(a, a->p[j]);
	if (p->ra && p->rra)
		p->rra = 0;
	p->rrr = 0;
	p->rr = 0;
	p->total = p->ra + p->rb + p->rra + p->rrb;
}

int	ft_order_start(t_pila *a)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (a->p[i] != ft_find_low(a))
		i++;
	while (j < a->len)
	{
		if (i < (a->len - 1) && a->p[i] > a->p[i + 1])
			break ;
		if (i == (a->len - 1) && a->p[i] > a->p[0])
			break ;
		if (++i == a->len)
			i = 0;
		j++;
	}
	if (j == (a->len - 1))
	{
		ft_order_end(a);
		return (1);
	}
	return (0);
}
