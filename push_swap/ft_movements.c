/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_movements.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 08:23:48 by atalaver          #+#    #+#             */
/*   Updated: 2022/11/02 09:46:49 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

void	ft_rev_rotate(t_pila *p)
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

void	ft_rotate(t_pila *p)
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

void	ft_swap(t_pila *p)
{
	int	aux;

	aux = p->p[p->len - 1];
	p->p[p->len - 1] = p->p[p->len - 2];
	p->p[p->len - 2] = aux;
}

void	ft_push(t_pila *dest, t_pila *ori)
{
	dest->len += 1;
	dest->p[dest->len - 1] = ori->p[ori->len - 1];
	ori->len -= 1;
}
