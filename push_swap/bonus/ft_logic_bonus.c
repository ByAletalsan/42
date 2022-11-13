/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_logic_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 17:56:56 by atalaver          #+#    #+#             */
/*   Updated: 2022/11/13 17:31:24 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_checker_bonus.h"

static int	ft_cmp(t_pila *a, t_pila *b, char *s)
{
	if (!ft_strncmp(s, "sa\n", 3))
		return (ft_swap_bonus(a), 1);
	else if (!ft_strncmp(s, "sb\n", 3))
		return (ft_swap_bonus(b), 1);
	else if (!ft_strncmp(s, "ra\n", 3))
		return (ft_rotate_bonus(a), 1);
	else if (!ft_strncmp(s, "rb\n", 3))
		return (ft_rotate_bonus(b), 1);
	else if (!ft_strncmp(s, "rra\n", 4))
		return (ft_rev_rotate_bonus(a), 1);
	else if (!ft_strncmp(s, "rrb\n", 4))
		return (ft_rev_rotate_bonus(b), 1);
	else
		return (0);
}

int	ft_logic_checker(t_pila *a, t_pila *b)
{
	char	*s;

	s = get_next_line(0);
	while (s)
	{
		if (!ft_cmp(a, b, s))
		{
			if (!ft_strncmp(s, "rr\n", 3))
				ft_rotate_both_bonus(a, b);
			else if (!ft_strncmp(s, "rrr\n", 4))
				ft_rev_rotate_both_bonus(a, b);
			else if (!ft_strncmp(s, "pa\n", 3))
				ft_push_bonus(a, b);
			else if (!ft_strncmp(s, "pb\n", 3))
				ft_push_bonus(b, a);
			else
				return (free(s), 1);
		}
		free(s);
		s = get_next_line(0);
	}
	free(s);
	return (0);
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
