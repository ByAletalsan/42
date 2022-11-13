/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_movements_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 08:23:48 by atalaver          #+#    #+#             */
/*   Updated: 2022/11/13 12:17:08 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_checker_bonus.h"

void	ft_rotate_bonus(t_pila *p)
{
	int	aux;
	int	i;

	i = 0;
	aux = p->p[0];
	while (i < p->len - 1)
	{
		p->p[i] = p->p[i + 1];
		i++;
	}
	p->p[p->len - 1] = aux;
}

void	ft_rev_rotate_bonus(t_pila *p)
{
	int	aux;
	int	i;

	i = p->len - 1;
	aux = p->p[i];
	while (i > 0)
	{
		p->p[i] = p->p[i - 1];
		i--;
	}
	p->p[0] = aux;
}

void	ft_swap_bonus(t_pila *p)
{
	int	aux;

	aux = p->p[0];
	p->p[0] = p->p[1];
	p->p[1] = aux;
}

void	ft_push_bonus(t_pila *dest, t_pila *ori)
{
	int	i;

	dest->len += 1;
	i = dest->len - 1;
	while (i > 0)
	{
		dest->p[i] = dest->p[i - 1];
		i--;
	}
	dest->p[0] = ori->p[0];
	ori->len -= 1;
	i = 0;
	while (i < ori->len)
	{
		ori->p[i] = ori->p[i + 1];
		i++;
	}
}

void	ft_rotate_both_bonus(t_pila *a, t_pila *b)
{
	int	aux;
	int	i;

	i = 0;
	aux = a->p[0];
	while (i < a->len - 1)
	{
		a->p[i] = a->p[i + 1];
		i++;
	}
	a->p[a->len - 1] = aux;
	i = 0;
	aux = b->p[0];
	while (i < b->len - 1)
	{
		b->p[i] = b->p[i + 1];
		i++;
	}
	b->p[b->len - 1] = aux;
}
