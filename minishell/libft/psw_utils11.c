/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   psw_utils11.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvasco-m <dvasco-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 20:19:44 by dvasco-m          #+#    #+#             */
/*   Updated: 2023/01/26 20:19:55 by dvasco-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	rotate(t_stl **stack, char ab)
{
	t_stl	*aux;
	int		n;

	n = ft_stacksize(*stack);
	if (n > 1)
	{
		aux = (*stack)->next;
		(ft_stacklast(*stack))->next = *stack;
		(*stack)->next = NULL;
		*stack = aux;
		if (ab == 'a')
			ft_printf("ra\n");
		if (ab == 'b')
			ft_printf("rb\n");
	}
}

void	rrotate(t_stl **stack_a, t_stl **stack_b, char simu)
{
	rotate(stack_a, 'c');
	rotate(stack_b, 'c');
	if (simu == 0)
		ft_printf("rr\n");
}

void	reverse_rotate(t_stl **stack, char ab)
{
	t_stl	*aux;
	int		n;

	n = ft_stacksize(*stack);
	if (n > 1)
	{
		aux = ft_stacklast(*stack);
		(ft_stack2last(*stack))->next = NULL;
		aux->next = *stack;
		*stack = aux;
		if (ab == 'a')
			ft_printf("rra\n");
		if (ab == 'b')
			ft_printf("rrb\n");
	}
}

void	rreverse_rotate(t_stl **stack_a, t_stl **stack_b, char simu)
{
	reverse_rotate(stack_a, 'c');
	reverse_rotate(stack_b, 'c');
	if (simu == 0)
		ft_printf("rrr\n");
}

void	push_n(t_stl **lstack_o, t_stl **lstack_d, int n, char ab_d)
{
	int	i;

	i = 0;
	while (i < n)
	{
		push(lstack_o, lstack_d, ab_d);
		i++;
	}
}
