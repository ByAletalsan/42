/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 08:47:47 by atalaver          #+#    #+#             */
/*   Updated: 2022/11/02 13:02:28 by atalaver         ###   ########.fr       */
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
	for (int i = a->len - 1; i >= 0; i--)
	{
		ft_printf("%i	", a->p[i]);
		if (i < b->len)
			ft_printf("%i", b->p[i]);
		ft_printf("\n");
	}
	ft_printf("--	--\n");
	ft_printf("A	 B\n");
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
	a = ft_fill(argc, argv);
	b = ft_fill(argc, argv);
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
