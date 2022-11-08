/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_two.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 12:53:25 by atalaver          #+#    #+#             */
/*   Updated: 2022/11/08 12:54:30 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

int	ft_return_find_low_of_top(t_pila *a, int n, int i)
{
	int	j;
	int	n_low;

	j = 0;
	while (j < a->len)
	{
		if (a->p[j] > n_low)
			n_low = a->p[j];
		j++;
	}
	if (n_low == n)
		return (ft_find_indice(a, ft_find_low(a)));
	if (i >= a->len)
		return (0);
	else
		return (i);
}
