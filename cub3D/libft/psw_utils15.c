/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   psw_utils15.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvasco-m <dvasco-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 20:22:28 by dvasco-m          #+#    #+#             */
/*   Updated: 2023/02/08 21:56:12 by dvasco-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_stl	*find_node(t_stl *stack, int i)
{
	while (i > 1 && stack != NULL)
	{
		stack = stack->next;
		i--;
	}
	return (stack);
}

int	evaluate_min(char *number, char *minint, int size, int i)
{
	int	valid;
	int	fin;

	valid = 1;
	fin = 0;
	while (valid && i < size && !fin)
	{
		if (number[i] < *(minint + i))
			fin = 1;
		else if (number[i] > *(minint + i))
			valid = 0;
		i++;
	}
	return (valid);
}

int	evaluate_max(char *number, char *maxint, int size, int i)
{
	int	valid;
	int	fin;

	valid = 1;
	fin = 0;
	while (valid && i < size && !fin)
	{
		if (number[i] < *(maxint + i))
			fin = 1;
		else if (number[i] > *(maxint + i))
			valid = 0;
		i++;
	}
	return (valid);
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

void	print_stacka(t_stl *stack_a)
{
	ft_printf("\nStack A: \n");
	while (stack_a != NULL)
	{
		ft_printf("%i\n", stack_a->number);
		stack_a = stack_a->next;
	}
}
