/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   psw_utils5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvasco-m <dvasco-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 20:15:25 by dvasco-m          #+#    #+#             */
/*   Updated: 2023/02/08 21:37:02 by dvasco-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**create_params(char **argv, int argc, char *array_params)
{
	char	**params;
	int		lzeros;

	lzeros = 0;
	array_params = create_array_params(argv, argc, &lzeros);
	if (array_params == NULL)
		return (NULL);
	params = ft_split(array_params, ' ');
	free(array_params);
	return (params);
}

void	reset_moves(t_simulation *xx)
{
	xx->pa = 0;
	xx->pb = 0;
	xx->ra = 0;
	xx->rb = 0;
	xx->rr = 0;
	xx->rra = 0;
	xx->rrb = 0;
	xx->rrr = 0;
	xx->sa = 0;
	xx->sb = 0;
	xx->ss = 0;
	xx->total = 0;
}

void	init_simulation(t_stl *stack_b)
{
	while (stack_b != NULL)
	{
		reset_moves(&(stack_b->moves));
		stack_b = stack_b->next;
	}
}

void	initial_moves(t_stack *lstack_a, t_stack *lstack_b)
{
	int	size;

	size = lstack_a->size;
	if (size < 3)
	{
		if (size == 2)
			ft_ord2(lstack_a);
	}
	else if (size == 3)
	{
		ft_ord3(lstack_a);
	}
	else
	{
		lstack_a->size = ft_stacksize(lstack_a->stack);
		push_n(&(lstack_a->stack), &(lstack_b->stack), size - 3, 'b');
		lstack_a->size = ft_stacksize(lstack_a->stack);
		lstack_b->size = ft_stacksize(lstack_b->stack);
		ft_ord3(lstack_a);
	}
}

void	calc_rb(t_stl *node, int size, int pos, t_simulation *xx)
{
	int	fin;

	fin = 0;
	while (xx->rb < size && pos != node->pos && !fin)
	{
		xx->rb += 1;
		node = node->next;
		if (node == NULL)
			fin = 1;
	}
}
