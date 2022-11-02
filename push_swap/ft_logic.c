/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_logic.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 12:21:18 by atalaver          #+#    #+#             */
/*   Updated: 2022/11/02 13:17:15 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

static int	ft_n_rev_rotate(t_pila *a, int n)
{
	int	i;

	i = 0;
	while (a->p[i] != n && i < a->len / 2)
		i++;
	if (a->p[i] == n)
		return (i + 1);
	else
		return (0);
}

static int	ft_n_rotate(t_pila *a, int n)
{
	int	i;

	i = a->len / 2;
	while (a->p[i] != n && i < a->len)
		i++;
	if (a->p[i] == n)
		return ((a->len - 1) - i);
	else
		return (0);
}

static int	ft_find_low(t_pila *a)
{
	int	i;
	int	n;

	i = 0;
	if (a->len == 0)
		return (0);
	n = a->p[0];
	while (i < a->len)
	{
		if (a->p[i] < n)
			n = a->p[i];
		i++;
	}
	return (n);
}

void	ft_logic(t_pila *a, t_pila *b)
{
	int	i;
	int	n;
	int	r;
	int	rr;

	while (a->len > 2)
	{
		n = ft_find_low(a);
		r = ft_n_rotate(a, n);
		rr = ft_n_rev_rotate(a, n);
		i = 0;
		while (i++ < r)
		{
			ft_printf("ra\n");
			ft_rotate(a);
		}
		i = 0;
		while (i++ < rr)
		{
			ft_printf("rra\n");
			ft_rev_rotate(a);
		}
		ft_push(b, a);
		ft_printf("pb\n");
	}
	if (a->p[0] < a->p[1])
	{
		ft_swap(a);
		ft_printf("sa\n");
	}
	while (b->len > 0)
	{
		ft_printf("pa\n");
		ft_push(a, b);
	}
}
