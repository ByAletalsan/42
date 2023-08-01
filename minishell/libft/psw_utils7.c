/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   psw_utils7.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvasco-m <dvasco-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 20:16:48 by dvasco-m          #+#    #+#             */
/*   Updated: 2023/01/26 20:16:59 by dvasco-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	calc_ramin(t_stl *node, int min, t_simulation *xx)
{
	int	fin;

	fin = 0;
	while (node->pos != min && !fin)
	{
		xx->ra += 1;
		node = node->next;
		if (node == NULL)
			fin = 1;
	}
}

void	calc_ramax(t_stl *node, int max, t_simulation *xx)
{
	int	fin;

	fin = 0;
	while (node->pos != max && !fin)
	{
		xx->ra += 1;
		node = node->next;
		if (node == NULL)
			fin = 1;
	}
	xx->ra += 1;
}

void	calc_ragen(t_stl *node, int size, int pos, t_simulation *xx)
{
	t_stl	*node_next;
	int		locate;

	locate = 0;
	node_next = node->next;
	while (xx->ra < size - 1 && !locate)
	{
		if (pos > node->pos && pos < node_next->pos)
			locate = 1;
		xx->ra += 1;
		node = node->next;
		if (node_next != NULL)
				node_next = node_next->next;
	}
	if (!locate)
		xx->ra = 0;
}

void	optimize_rr(t_simulation *xx)
{
	if (xx->rb >= xx->ra)
	{
		xx->rb = xx->rb - xx->ra;
		xx->rr = xx->ra;
		xx->ra = 0;
	}
	else if (xx->rb < xx->ra)
	{
		xx->ra = xx->ra - xx->rb;
		xx->rr = xx->rb;
		xx->rb = 0;
	}
	xx->total = xx->ra + xx->rb + xx->rr;
}

void	calc_rrb(t_stl *node, int size, int pos, t_simulation *xx)
{
	int	offset;

	offset = 0;
	while (pos != node->pos)
	{
		offset += 1;
		node = node->next;
	}
	if (offset != 0)
	{
		while (xx->rrb < (size - offset))
			xx->rrb += 1;
	}
}
