/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_arg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 10:10:04 by atalaver          #+#    #+#             */
/*   Updated: 2022/11/02 12:14:31 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

int	ft_check_rep(t_pila *a)
{
	int	i;
	int	j;

	i = 0;
	while (i < a->len)
	{
		j = i + 1;
		while (j < a->len)
		{
			if (a->p[i] == a->p[j])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	ft_check_limit(int argc, char **argv)
{
	int		i;
	long	n;

	i = 1;
	while (i < argc)
	{
		n = ft_atol(argv[i]);
		if (n > INT_MAX || n < INT_MIN)
			return (1);
		i++;
	}
	return (0);
}

int	ft_check_digit(int argc, char **argv)
{
	int	i;
	int	j;
	int	end;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j] == '-' || argv[i][j] == '+')
				j++;
		if (argv[i][j] == '\0')
			return (1);
		while (argv[i][j] != '\0')
		{
			if (!ft_isdigit(argv[i][j]))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
