/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_movements.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 08:23:48 by atalaver          #+#    #+#             */
/*   Updated: 2022/11/07 13:43:03 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

void	ft_rotate(t_pila *p)
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
	ft_printf("r%c\n", p->c);
}

void	ft_rev_rotate(t_pila *p)
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
	ft_printf("rr%c\n", p->c);
}

void	ft_swap(t_pila *p)
{
	int	aux;

	aux = p->p[0];
	p->p[0] = p->p[1];
	p->p[1] = aux;
	ft_printf("s%c\n", p->c);
}

void	ft_push(t_pila *dest, t_pila *ori)
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
	ft_printf("p%c\n", dest->c);
}
