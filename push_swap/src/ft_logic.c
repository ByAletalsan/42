/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_logic.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 12:21:18 by atalaver          #+#    #+#             */
/*   Updated: 2022/11/08 14:39:13 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

int	ft_n_rev_rotate(t_pila *a, int n)
{
	int	i;

	i = a->len - 1;
	while (a->p[i] != n && i > a->len / 2)
		i--;
	if (a->p[i] == n)
		return (a->len - i);
	else
		return (0);
}

int	ft_n_rotate(t_pila *a, int n)
{
	int	i;

	i = 0;
	while (a->p[i] != n && i < a->len / 2)
		i++;
	if (a->p[i] == n)
		return (i);
	else
		return (0);
}

int	ft_find_low(t_pila *a)
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

void	ft_order_end(t_pila *a)
{
	int	i;
	int	low;
	int	r;
	int	rr;

	i = 0;
	low = ft_find_low(a);
	r = ft_n_rotate(a, low);
	rr = ft_n_rev_rotate(a, low);
	if (r && rr)
		rr = 0;
	while (i < r || i < rr)
	{
		if (r)
			ft_rotate(a);
		else
			ft_rev_rotate(a);
		i++;
	}
}

void	ft_logic(t_pila *a, t_pila *b)
{
	if (a->len == 2)
		ft_order_two(a);
	if (a->len == 3)
		ft_order_three(a);
	if (a->len == 4)
		ft_order_four(a, b);
	if (a->len == 5)
		ft_order_five(a, b);
	if (a->len > 5)
		ft_order(a, b);
}
