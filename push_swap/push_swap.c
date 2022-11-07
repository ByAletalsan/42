/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 08:47:47 by atalaver          #+#    #+#             */
/*   Updated: 2022/11/07 13:41:13 by atalaver         ###   ########.fr       */
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

static void	ft_print(t_pila *a, t_pila *b)
{
	ft_printf("A: ");
	for (int i = 0; i < a->len; i++)
		ft_printf("%i ", a->p[i]);
	ft_printf("\nB: ");
	for (int i = 0; i < b->len; i++)
		ft_printf("%i ", b->p[i]);
	ft_printf("\n");
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
		return (1);
	b->len = 0;
	if (ft_check_rep(a))
	{
		ft_printf("Error\n");
		return (1);
	}
	ft_logic(a, b);
	ft_print(a, b);
	ft_free(a, b);
	return (0);
}
