/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 11:13:48 by atalaver          #+#    #+#             */
/*   Updated: 2022/10/27 11:40:44 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
	int	r;

	i = 0;
	r = 0;
	if (b->menos == 0 && p == 0)
	{
		while (i < (b->width - b->limit))
		{
			if (b->cero == 0 || b->punto == 1)
				r += ft_print_char(' ');
			else if (b->almoadilla == 0)
				r += ft_print_char('0');
			i++;
		}
	}
	if (b->menos == 1 && p == 1)
	{
		while (i < (b->width - b->limit))
		{
			r += ft_print_char(' ');
			i++;
		}
	}
	return (r);
}

int	ft_print_hexa(unsigned int n, char format, t_bonus *b)
{
	int	r;

	r = 0;
	if (b->limit < ft_memlen(n, b))
		b->limit = ft_memlen(n, b);
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
	if (n == 0 && b->limit > 0)
		r += write(1, "0", 1);
	else if (b->limit > 0)
	{
		ft_itemem(n, format);
		r += ft_memlen(n, b);
	}
	r += ft_print_spaces_hex(b, 1);
	return (r);
}
