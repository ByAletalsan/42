/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_order_to_four.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 12:41:00 by atalaver          #+#    #+#             */
/*   Updated: 2022/11/07 13:45:47 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

void	ft_order_two(t_pila *a)
{
	if (a->p[0] > a->p[1])
		ft_swap(a);
}

void	ft_order_three(t_pila *a, t_pila *b)
{
	int	i;
	int	low;

	if ((a->p[0] < a->p[1]) && (a->p[1] < a->p[2]))
		return ;
	low = ft_find_low(a);
	i = 0;
	while (i < ft_n_rotate(a, low) || i < ft_n_rev_rotate(a, low))
	{
		if (ft_n_rotate(a, low))
			ft_rotate(a);
		else
			ft_rev_rotate(a);
		i++;
	}
	if (a->p[1] > a->p[2])
	{
		ft_push(b, a);
		ft_order_two(a);
		ft_push(a, b);
	}
}
