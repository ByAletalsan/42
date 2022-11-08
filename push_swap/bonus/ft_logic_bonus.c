/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_logic_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 17:56:56 by atalaver          #+#    #+#             */
/*   Updated: 2022/11/08 19:27:08 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_checker_bonus.h"

void	ft_logic_checker(t_pila *a, t_pila *b)
{
	char	*s;

	s = get_next_line(0);
	while (s)
	{
		if (ft_strncmp(s, "sa", 2))
			ft_swap_bonus(a);
		if (ft_strncmp(s, "sb", 2))
			ft_swap_bonus(b);
		if (ft_strncmp(s, "ra", 2))
			ft_rotate_bonus(a);
		if (ft_strncmp(s, "rb", 2))
			ft_rotate_bonus(b);
		if (ft_strncmp(s, "rra", 3))
			ft_rev_rotate_bonus(a);
		if (ft_strncmp(s, "rrb", 3))
			ft_rev_rotate_bonus(b);
		if (ft_strncmp(s, "rr", 2))
			ft_rotate_both_bonus(a, b);
		if (ft_strncmp(s, "rrr", 3))
			ft_rev_rotate_both_bonus(a, b);
		if (ft_strncmp(s, "pa", 2))
			ft_push_bonus(a, b);
		if (ft_strncmp(s, "pb", 2))
			ft_push_bonus(b, a);
		s = get_next_line(0);
	}
}

void	ft_check_order(t_pila *a, t_pila *b)
{
	int	i;

	if (b->len > 0)
	{
		ft_printf("KO\n");
		return ;
	}
	i = 0;
	while (i < (a->len - 1))
	{
		if (a->p[i] > a->p[i + 1])
		{
			ft_printf("KO\n");
			return ;
		}
		i++;
	}
	ft_printf("OK\n");
}
