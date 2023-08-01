/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   psw_utils16.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvasco-m <dvasco-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 12:14:23 by dvasco-m          #+#    #+#             */
/*   Updated: 2023/02/08 23:22:24 by dvasco-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	calc_maxmin(t_stack *lstack_a)
{
	t_stl	*node;

	node = lstack_a->stack;
	lstack_a->max = node->pos;
	while (node != NULL)
	{
		if (node->pos > lstack_a->max)
			lstack_a->max = node->pos;
		node = node->next;
	}
	node = lstack_a->stack;
	lstack_a->min = node->pos;
	while (node != NULL)
	{
		if (node->pos < lstack_a->min)
			lstack_a->min = node->pos;
		node = node->next;
	}
}

void	calc_rragen(t_stl *node, int size, int pos, t_simulation *xx)
{
	int		offset;

	offset = calc_offset_rragen(node, size, pos);
	if (offset != size)
	{
		while (xx->rra < (size - offset))
			xx->rra += 1;
	}
}

void	calc_rramax(t_stl *node, int max, int size, t_simulation *xx)
{
	int	offset;

	offset = 0;
	while (node->pos != max)
	{
		offset += 1;
		node = node->next;
	}
	while (xx->rra < (size - offset) - 1)
		xx->rra += 1;
}

void	calc_rramin(t_stl *node, int min, int size, t_simulation *xx)
{
	int	offset;

	offset = 0;
	while (node->pos != min)
	{
		offset += 1;
		node = node->next;
	}
	if (offset != 0)
	{
		while (xx->rra < (size - offset))
			xx->rra += 1;
	}
}

int	calc_offset_rragen(t_stl *node, int size, int pos)
{
	t_stl	*node_next;
	int		locate;
	int		offset;

	locate = 0;
	offset = 0;
	node_next = node->next;
	while (offset < size && !locate)
	{
		if (offset != size - 1)
		{
			if (pos > node->pos && pos < node_next->pos)
				locate = 1;
			node = node->next;
			if (node_next != NULL)
				node_next = node_next->next;
		}
		offset += 1;
	}
	return (offset);
}
