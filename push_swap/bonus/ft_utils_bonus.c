/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 19:28:33 by atalaver          #+#    #+#             */
/*   Updated: 2022/11/08 19:49:25 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_checker_bonus.h"

void	ft_rev_rotate_both_bonus(t_pila *a, t_pila *b)
{
	int	aux;
	int	i;

	i = a->len - 1;
	aux = a->p[i];
	while (i > 0)
	{
		a->p[i] = a->p[i - 1];
		i--;
	}
	a->p[0] = aux;
	i = b->len - 1;
	aux = b->p[i];
	while (i > 0)
	{
		b->p[i] = b->p[i - 1];
		i--;
	}
	b->p[0] = aux;
}
