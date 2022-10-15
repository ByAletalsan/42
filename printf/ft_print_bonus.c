/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 19:48:11 by atalaver          #+#    #+#             */
/*   Updated: 2022/10/15 18:20:42 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_memlen(unsigned int n)
{
	int	i;

	i = 0;
	while (n != 0)
	{
		i++;
		n = n / 16;
	}
	return (i);
}

int	ft_print_spaces(t_bonus *b, unsigned long long n, int p)
{
	int	i;

	i = 0;
	if (b->menos == 0 && (b->cero == 0 || n == 0) && p == 0)
	{
		while (i < (b->width - b->limit))
		{
			ft_print_char(' ');
			i++;
		}
	}
	if (b->menos == 1 && p == 1)
	{
		while (i < (b->width - b->limit))
		{
			ft_print_char(' ');
			i++;
		}
	}
	return (i);
}

int	ft_print_ceros(t_bonus *b)
{
	int	i;

	i = 0;
	if (b->cero == 1 && b->menos == 0)
	{
		while (i < (b->width - b->limit))
		{
			ft_print_char('0');
			i++;
		}
	}
	return (i);
}

int	ft_print_spaces_int(t_bonus *b, int p)
{
	int	i;

	i = 0;
	if (b->menos == 0 && p == 0 && (b->cero == 0 || b->punto == 1))
	{
		while (i < (b->width - b->limit))
		{
			ft_print_char(' ');
			i++;
		}
	}
	if (b->menos == 1 && p == 1)
	{
		while (i < (b->width - b->limit))
		{
			ft_print_char(' ');
			i++;
		}
	}
	return (i);
}

int	ft_print_ceros_hex(t_bonus *b, unsigned int n)
{
	int	i;
	int	l;

	i = 0;
	l = ft_memlen(n);
	if (n == 0)
		l = 1;
	if ((b->cero == 1 || b->punto == 1) && b->menos == 0)
	{
		while (i < (b->limit - l - b->almoadilla * 2))
		{
			ft_print_char('0');
			i++;
		}
	}
	return (i);
}
