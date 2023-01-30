/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 08:47:47 by atalaver          #+#    #+#             */
/*   Updated: 2023/01/30 15:45:13 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

static void	ft_free(t_pila *a, t_pila *b)
{
	free(a->p);
	a->p = NULL;
	free(a);
	a = NULL;
	free(b->p);
	b->p = NULL;
	free(b);
	b = NULL;
}

int	main(int argc, char **argv)
{
	t_pila	*a;
	t_pila	*b;

	if (argc < 2)
		return (1);
	if (ft_check_digit(argc, argv) || ft_check_limit(argc, argv))
	{
		ft_printf("Error\n");
		return (1);
	}
	a = ft_fill(argc, argv, 'a');
	b = ft_fill(argc, argv, 'b');
	if (!a || !b)
		return (ft_free(a, b), 1);
	b->len = 0;
	if (ft_check_rep(a))
	{
		ft_printf("Error\n");
		return (ft_free(a, b), 1);
	}
	ft_logic(a, b);
	ft_free(a, b);
	return (0);
}
