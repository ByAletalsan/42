/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push_start.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 12:37:04 by atalaver          #+#    #+#             */
/*   Updated: 2022/11/09 15:36:14 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

static int	ft_find_top_number(t_pila *a)
{
	int	i;
	int	top;

	i = 0;
	top = a->p[i];
	while (i < a->len)
	{
		if (a->p[i] > top)
			top = a->p[i];
		i++;
	}
	return (top);
}

void	ft_push_start(t_pila *a, t_pila *b)
{
	int	i;
	int	top;
	int	len;

	top = ft_find_top_number(a);
	len = a->len;
	i = a->len - 3;
	while (--i >= 0)
	{
		ft_push(b, a);
		if (b->p[0] < (top / 2) && len > 150)
			ft_rotate(b);
	}
	ft_order_three(a);
}
