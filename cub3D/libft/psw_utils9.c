/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   psw_utils9.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvasco-m <dvasco-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 20:18:03 by dvasco-m          #+#    #+#             */
/*   Updated: 2023/01/26 21:16:32 by dvasco-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	save_moves(t_simulation *xx, t_stack *lstack_b, int pos)
{
	t_stl	*node;

	node = lstack_b->stack;
	while (node->pos != pos)
		node = node->next;
	node->moves.pa = xx->pa;
	node->moves.pb = xx->pb;
	node->moves.ra = xx->ra;
	node->moves.rb = xx->rb;
	node->moves.rr = xx->rr;
	node->moves.rra = xx->rra;
	node->moves.rrb = xx->rrb;
	node->moves.rrr = xx->rrr;
	node->moves.sa = xx->sa;
	node->moves.sb = xx->sb;
	node->moves.ss = xx->ss;
	node->moves.total = xx->total;
}

void	calc_moves(t_stack *lstack_a, t_stack *lstack_b, int pos)
{
	t_simulation	uu;
	t_simulation	ud;
	t_simulation	du;
	t_simulation	dd;
	int				min;

	w_uu(lstack_a, lstack_b, pos, &uu);
	w_ud(lstack_a, lstack_b, pos, &ud);
	w_du(lstack_a, lstack_b, pos, &du);
	w_dd(lstack_a, lstack_b, pos, &dd);
	min = uu.total;
	if (ud.total < min)
		min = ud.total;
	if (du.total < min)
		min = du.total;
	if (dd.total < min)
		min = dd.total;
	if (uu.total == min)
		save_moves(&uu, lstack_b, pos);
	if (ud.total == min)
		save_moves(&ud, lstack_b, pos);
	if (du.total == min)
		save_moves(&du, lstack_b, pos);
	if (dd.total == min)
		save_moves(&dd, lstack_b, pos);
}

int	make_simulation(t_stack	*lstack_a, t_stack *lstack_b)
{
	t_stl	*node;
	int		min;
	int		best;

	node = lstack_b->stack;
	while (node != NULL)
	{
		calc_moves(lstack_a, lstack_b, node->pos);
		node = node->next;
	}
	node = lstack_b->stack;
	best = node->pos;
	min = node->moves.total;
	while (node != NULL)
	{
		if (node->moves.total < min)
		{
			min = node->moves.total;
			best = node->pos;
		}
		node = node->next;
	}
	return (best);
}

void	make_best_move(t_stack *s_a, t_stack *s_b, int selected)
{
	t_stl	*node;

	node = s_b->stack;
	while (node->pos != selected)
		node = node->next;
	rrotate_n(&(s_a->stack), &(s_b->stack), 0, node->moves.rr);
	rotate_n(&(s_a->stack), node->moves.ra, s_a->ab);
	rotate_n(&(s_b->stack), node->moves.rb, s_b->ab);
	rreverse_rotate_n(&(s_a->stack), &(s_b->stack), 0, node->moves.rrr);
	reverse_rotate_n(&(s_b->stack), node->moves.rrb, s_b->ab);
	reverse_rotate_n(&(s_a->stack), node->moves.rra, s_a->ab);
	push(&(s_b->stack), &(s_a->stack), s_a->ab);
}

void	actualize_stacks(t_stack *lstack_a, t_stack *lstack_b)
{
	lstack_a->size = ft_stacksize(lstack_a->stack);
	lstack_b->size = ft_stacksize(lstack_b->stack);
}
