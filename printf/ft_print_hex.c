/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 11:13:48 by atalaver          #+#    #+#             */
/*   Updated: 2022/10/15 16:04:43 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

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

static void	ft_print_hex(unsigned int n, char format)
{
	if (n <= 9)
		ft_putchar_fd((n + '0'), 1);
	else
	{
		if (format == 'x')
			ft_putchar_fd((n - 10 + 'a'), 1);
		if (format == 'X')
			ft_putchar_fd((n - 10 + 'A'), 1);
	}
}

static void	ft_itemem(unsigned int n, char format)
{
	if (n >= 16)
	{
		ft_itemem(n / 16, format);
		ft_itemem(n % 16, format);
	}
	else
		ft_print_hex(n, format);
}

static int	ft_print_spaces_hex(t_bonus *b, int p)
{
	int	i;

	i = 0;
	if (b->menos == 0 && p == 0)
	{
		while (i < (b->width - b->limit))
		{
			if (b->cero == 0)
				ft_print_char(' ');
			else
				ft_print_char('0');
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

int	ft_print_hexa(unsigned int n, char format, t_bonus *b)
{
	int	r;

	r = 0;
	if (b->limit < ft_memlen(n) && b->punto == 0)
		b->limit = ft_memlen(n);
	if (n == 0 && b->punto == 0)
		b->limit = 1;
	if (n != 0)
		b->limit += b->almoadilla * 2;
	r += ft_print_spaces_hex(b, 0);
	if (b->almoadilla == 1 && n != 0)
	{
		if (format == 'x')
			r += write(1, "0x", 2);
		else
			r += write(1, "0X", 2);
	}
	r += ft_print_ceros_hex(b, n);
	if (n == 0)
		r += write(1, "0", 1);
	else
	{
		ft_itemem(n, format);
		r += ft_memlen(n);
	}
	r += ft_print_spaces_hex(b, 1);
	return (r);
}
