/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   psw_utils10.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvasco-m <dvasco-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 20:18:56 by dvasco-m          #+#    #+#             */
/*   Updated: 2023/01/26 20:19:13 by dvasco-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	final_order(t_stack *s_a)
{
	t_stl	*node;
	int		position;

	node = s_a->stack;
	position = 1;
	while (node->pos != s_a->min && node->pos != 1)
	{
		position++;
		node = node->next;
	}
	if (position <= (s_a->size - position) && position != 1)
		rotate_n(&(s_a->stack), position - 1, s_a->ab);
	if (position > (s_a->size - position) && position != 1)
		reverse_rotate_n(&(s_a->stack), s_a->size - position + 1, s_a->ab);
}

t_stl	*push_swap(t_stl *stack)
{
	t_stack		lstack_a;
	t_stack		lstack_b;
	int			selected;

	cre_lstks(&lstack_a, &lstack_b, stack);
	if (lstack_a.size > 3)
	{
		initial_moves(&lstack_a, &lstack_b);
		while (lstack_b.stack != NULL)
		{	
			init_simulation(lstack_b.stack);
			calc_maxmin(&lstack_a);
			selected = make_simulation(&lstack_a, &lstack_b);
			make_best_move(&lstack_a, &lstack_b, selected);
			actualize_stacks(&lstack_a, &lstack_b);
		}
		final_order(&lstack_a);
	}
	else if (lstack_a.size == 3)
		ft_ord3(&lstack_a);
	else if (lstack_a.size == 2)
		ft_ord2(&lstack_a);
	return (lstack_a.stack);
}

void	swap(t_stl **stack, char ab)
{
	t_stl	*aux1;
	t_stl	*aux2;
	int		n;

	n = ft_stacksize(*stack);
	if (n > 1)
	{
		aux1 = ((*stack)->next);
		aux2 = ((*stack)->next)->next;
		((*stack)->next)->next = *stack;
		(*stack)->next = aux2;
		*stack = aux1;
	}
	if (ab == 'a')
		ft_printf("sa\n");
	if (ab == 'b')
		ft_printf("sb\n");
}

void	sswap(t_stl **stack_a, t_stl **stack_b, char simu)
{
	swap(stack_a, 'c');
	swap(stack_b, 'c');
	if (simu == 0)
		ft_printf("ss\n");
}

void	push(t_stl **stack_o, t_stl **stack_d, char ab_d)
{
	t_stl	*aux;

	aux = NULL;
	if (*stack_o != NULL)
	{
		if (*stack_d == NULL)
		{
			*stack_d = *stack_o;
			*stack_o = (*stack_o)->next;
			(*stack_d)->next = NULL;
		}
		else
		{
			aux = *stack_o;
			*stack_o = (*stack_o)->next;
			aux->next = *stack_d;
			*stack_d = aux;
		}
		if (ab_d == 'a')
			ft_printf("pa\n");
		if (ab_d == 'b')
			ft_printf("pb\n");
	}
}
