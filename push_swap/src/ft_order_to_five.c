/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_order_to_five.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 12:41:00 by atalaver          #+#    #+#             */
/*   Updated: 2022/11/08 14:34:28 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

void	ft_order_two(t_pila *a)
{
	if (a->p[0] > a->p[1])
		ft_swap(a);
}

void	ft_order_three(t_pila *a)
{
	if ((a->p[0] < a->p[1]) && (a->p[1] < a->p[2]) && (a->p[2] > a->p[0]))
		return ;
	if ((a->p[0] > a->p[1]) && (a->p[1] < a->p[2]) && (a->p[2] > a->p[0]))
		ft_swap(a);
	if ((a->p[0] > a->p[1]) && (a->p[1] > a->p[2]) && (a->p[2] < a->p[0]))
	{
		ft_swap(a);
		ft_rev_rotate(a);
	}
	if ((a->p[0] > a->p[1]) && (a->p[1] < a->p[2]) && (a->p[2] < a->p[0]))
		ft_rotate(a);
	if ((a->p[0] < a->p[1]) && (a->p[1] > a->p[2]) && (a->p[2] > a->p[0]))
	{
		ft_swap(a);
		ft_rotate(a);
	}
	if ((a->p[0] < a->p[1]) && (a->p[1] > a->p[2]) && (a->p[2] < a->p[0]))
		ft_rev_rotate(a);
}

void	ft_order_four(t_pila *a, t_pila *b)
{
	int	i;

	i = 0;
	while (i < 3 && a->p[i] < a->p[i + 1])
		i++;
	if (i == 3)
		return ;
	i = 0;
	ft_push(b, a);
	ft_order_three(a);
	while (i < 3)
	{
		if (a->p[i] > b->p[0])
			break ;
		i++;
	}
	if (i == 2)
		ft_rev_rotate(a);
	else if (i <= 1)
	{
		while (i-- > 0)
			ft_rotate(a);
	}
	ft_push(a, b);
	ft_order_end(a);
}

static int	ft_order_five_start(t_pila *a, t_pila *b)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (a->p[i] != ft_find_low(a))
		i++;
	while (j < 5)
	{
		if (i < 4 && a->p[i] > a->p[i + 1])
			break ;
		if (i == 4 && a->p[i] > a->p[0])
			break ;
		if (++i == 5)
			i = 0;
		j++;
	}
	if (j == 4)
	{
		ft_order_end(a);
		return (1);
	}
	ft_push(b, a);
	ft_push(b, a);
	return (0);
}

void	ft_order_five(t_pila *a, t_pila *b)
{
	int	i;
	int	j;

	j = -1;
	if (ft_order_five_start(a, b))
		return ;
	ft_order_three(a);
	while (++j < 2)
	{
		i = ft_find_low_of_top(a, b->p[0]);
		if (i > a->len / 2)
		{
			while (i++ < a->len)
				ft_rev_rotate(a);
		}
		else if (i <= a->len / 2)
		{
			while (i-- > 0)
				ft_rotate(a);
		}
		ft_push(a, b);
	}
	ft_order_end(a);
}
