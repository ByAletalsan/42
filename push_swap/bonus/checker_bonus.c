/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 17:37:26 by atalaver          #+#    #+#             */
/*   Updated: 2022/11/13 17:09:18 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_checker_bonus.h"

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

static void	ft_run(t_pila *a, t_pila *b)
{
	if (ft_logic_checker(a, b))
	{
		ft_putstr_fd("Error\n", STDERR);
		ft_free(a, b);
		return ;
	}
	ft_check_order(a, b);
	ft_free(a, b);
	return ;
}

int	main(int argc, char **argv)
{
	t_pila	*a;
	t_pila	*b;

	if (argc < 2)
		return (1);
	if (ft_check_digit(argc, argv) || ft_check_limit(argc, argv))
	{
		ft_putstr_fd("Error\n", STDERR);
		return (1);
	}
	a = ft_fill(argc, argv, 'a');
	b = ft_fill(argc, argv, 'b');
	if (!a || !b)
		return (ft_free(a, b), 1);
	b->len = 0;
	if (ft_check_rep(a))
	{
		ft_putstr_fd("Error\n", STDERR);
		return (ft_free(a, b), 1);
	}
	ft_run(a, b);
	return (0);
}
