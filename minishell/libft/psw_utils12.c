/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   psw_utils12.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvasco-m <dvasco-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 20:20:30 by dvasco-m          #+#    #+#             */
/*   Updated: 2023/01/26 20:20:42 by dvasco-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	rotate_n(t_stl **stack, int n, char ab)
{
	int	i;

	i = 0;
	while (i < n)
	{
		rotate(stack, ab);
		i++;
	}
}

void	rrotate_n(t_stl **stack_a, t_stl **stack_b, char simu, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		rrotate(stack_a, stack_b, simu);
		i++;
	}
}

void	reverse_rotate_n(t_stl **stack, int n, char ab)
{
	int	i;

	i = 0;
	while (i < n)
	{
		reverse_rotate(stack, ab);
		i++;
	}
}

void	rreverse_rotate_n(t_stl **stack_a, t_stl **stack_b, char simu, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		rreverse_rotate(stack_a, stack_b, simu);
		i++;
	}
}

void	ft_ord3(t_stack *lstack_a)
{
	if ((lstack_a->stack->number < lstack_a->stack->next->number)
		&& (lstack_a->stack->next->number > lstack_a->stack->next->next->number)
		&& (lstack_a->stack->next->next->number > lstack_a->stack->number))
		rotate(&(lstack_a->stack), 'a');
	if ((lstack_a->stack->number > lstack_a->stack->next->number)
		&& (lstack_a->stack->next->number > lstack_a->stack->next->next->number)
		&& (lstack_a->stack->next->next->number < lstack_a->stack->number))
		swap(&(lstack_a->stack), 'a');
	if ((lstack_a->stack->number > lstack_a->stack->next->number)
		&& (lstack_a->stack->next->number < lstack_a->stack->next->next->number)
		&& (lstack_a->stack->next->next->number > lstack_a->stack->number))
		swap(&(lstack_a->stack), 'a');
	else if ((lstack_a->stack->number < lstack_a->stack->next->number)
		&& (lstack_a->stack->next->number > lstack_a->stack->next->next->number)
		&& (lstack_a->stack->next->next->number < lstack_a->stack->number))
		reverse_rotate(&(lstack_a->stack), 'a');
	else if ((lstack_a->stack->number > lstack_a->stack->next->number)
		&& (lstack_a->stack->next->number < lstack_a->stack->next->next->number)
		&& (lstack_a->stack->next->next->number < lstack_a->stack->number))
		rotate(&(lstack_a->stack), 'a');
}
