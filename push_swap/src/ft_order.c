/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_order.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 14:35:25 by atalaver          #+#    #+#             */
/*   Updated: 2022/11/09 12:47:22 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

static void	ft_optimizer(t_cost *min)
{
	while (min->ra > 0 && min->rb > 0)
	{
		min->ra -= 1;
		min->rb -= 1;
		min->rr += 1;
	}
	while (min->rra > 0 && min->rrb > 0)
	{
		min->rra -= 1;
		min->rrb -= 1;
		min->rrr += 1;
	}
}

static void	ft_run(t_cost *min, t_pila *a, t_pila *b)
{
	int	i;

	i = 0;
	while (i++ < min->ra)
		ft_rotate(a);
	i = 0;
	while (i++ < min->rb)
		ft_rotate(b);
	i = 0;
	while (i++ < min->rra)
		ft_rev_rotate(a);
	i = 0;
	while (i++ < min->rrb)
		ft_rev_rotate(b);
	i = 0;
	while (i++ < min->rr)
		ft_rotate_both(a, b);
	i = 0;
	while (i++ < min->rrr)
		ft_rev_rotate_both(a, b);
	ft_push(a, b);
}

static void	ft_copy_cost(t_cost *min, t_cost *c)
{
	min->ra = c->ra;
	min->rb = c->rb;
	min->rra = c->rra;
	min->rrb = c->rrb;
	min->total = c->total;
}

static void	ft_find_cost(t_pila *a, t_pila *b, t_cost *c)
{
	int		i;
	t_cost	*min;

	i = 0;
	min = ft_ini_cost();
	while (i < b->len)
	{
		ft_cost(a, b, i, c);
		if (c->total == 0)
			break ;
		if (c->total < min->total || i == 0)
			ft_copy_cost(min, c);
		i++;
	}
	ft_optimizer(min);
	ft_run(min, a, b);
	free(min);
}

void	ft_order(t_pila *a, t_pila *b)
{
	t_cost	*c;

	if (ft_order_start(a))
		return ;
	ft_push_start(a, b);
	c = ft_ini_cost();
	while (b->len > 0)
	{
		ft_find_cost(a, b, c);
	}
	free(c);
	ft_order_end(a);
}
