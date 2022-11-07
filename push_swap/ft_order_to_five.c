/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_order_to_five.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 12:41:00 by atalaver          #+#    #+#             */
/*   Updated: 2022/11/07 17:23:57 by atalaver         ###   ########.fr       */
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
