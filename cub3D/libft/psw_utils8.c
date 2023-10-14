/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   psw_utils8.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvasco-m <dvasco-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 20:17:28 by dvasco-m          #+#    #+#             */
/*   Updated: 2023/01/26 20:17:36 by dvasco-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	optimize_rrr(t_simulation *xx)
{
	if (xx->rrb >= xx->rra)
	{
		xx->rrb = xx->rrb - xx->rra;
		xx->rrr = xx->rra;
		xx->rra = 0;
	}
	else if (xx->rrb < xx->rra)
	{
		xx->rra = xx->rra - xx->rrb;
		xx->rrr = xx->rrb;
		xx->rrb = 0;
	}
	xx->total = xx->rra + xx->rrb + xx->rrr;
}

void	w_uu(t_stack *s_a, t_stack *s_b, int pos, t_simulation *uu)
{
	reset_moves(uu);
	calc_rb(s_b->stack, s_b->size, pos, uu);
	if (pos < s_a->min)
		calc_ramin(s_a->stack, s_a->min, uu);
	else if (pos > s_a->max)
		calc_ramax(s_a->stack, s_a->max, uu);
	else
		calc_ragen(s_a->stack, s_a->size, pos, uu);
	optimize_rr(uu);
	uu->pa = 1;
	uu->total += 1;
}

void	w_du(t_stack *s_a, t_stack *s_b, int pos, t_simulation *du)
{
	reset_moves(du);
	calc_rb(s_b->stack, s_b->size, pos, du);
	if (pos < s_a->min)
		calc_rramin(s_a->stack, s_a->min, s_a->size, du);
	else if (pos > s_a->max)
		calc_rramax(s_a->stack, s_a->max, s_a->size, du);
	else
		calc_rragen(s_a->stack, s_a->size, pos, du);
	du->pa = 1;
	du->total = du->rb + du->rra + du->pa;
}

void	w_ud(t_stack *s_a, t_stack *s_b, int pos, t_simulation *ud)
{
	reset_moves(ud);
	calc_rrb(s_b->stack, s_b->size, pos, ud);
	if (pos < s_a->min)
		calc_ramin(s_a->stack, s_a->min, ud);
	else if (pos > s_a->max)
		calc_ramax(s_a->stack, s_a->max, ud);
	else
		calc_ragen(s_a->stack, s_a->size, pos, ud);
	ud->pa = 1;
	ud->total = ud->rrb + ud->ra + ud->pa;
}

void	w_dd(t_stack *s_a, t_stack *s_b, int pos, t_simulation *dd)
{
	reset_moves(dd);
	calc_rrb(s_b->stack, s_b->size, pos, dd);
	if (pos < s_a->min)
		calc_rramin(s_a->stack, s_a->min, s_a->size, dd);
	else if (pos > s_a->max)
		calc_rramax(s_a->stack, s_a->max, s_a->size, dd);
	else
		calc_rragen(s_a->stack, s_a->size, pos, dd);
	optimize_rrr(dd);
	dd->pa = 1;
	dd->total += 1;
}
