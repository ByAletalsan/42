/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_memory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 20:06:26 by atalaver          #+#    #+#             */
/*   Updated: 2022/10/16 12:43:22 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_memlen_memory(unsigned long long n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (3);
	while (n != 0)
	{
		i++;
		n = n / 16;
	}
	return (i);
}

static void	ft_print_hex(unsigned long long n)
{
	if (n <= 9)
		ft_putchar_fd((n + '0'), 1);
	else
		ft_putchar_fd((n - 10 + 'a'), 1);
}

static void	ft_itemem(unsigned long long n)
{
	if (n >= 16)
	{
		ft_itemem(n / 16);
		ft_itemem(n % 16);
	}
	else
		ft_print_hex(n);
}

int	ft_print_memory(unsigned long long n, t_bonus *b)
{
	int	r;

	r = 0;
	if (b->limit < ft_memlen_memory(n))
		b->limit = ft_memlen_memory(n);
	/*if (n == 0)
		b->limit = 5;
	else
		b->limit = ft_memlen_memory(n) + 2;
	if (b->mas == 1)
		b->limit += 1;*/
	r += ft_print_space_memory(b, n, 0);
	if (n == 0)
		r += write(1, "(nil)", 5);
	else
	{
		if (b->mas == 1)
			r += ft_print_char('+');
		r += write(1, "0x", 2);
		r += ft_print_ceros(b, ft_memlen_memory(n));
		ft_itemem(n);
		r += ft_memlen_memory(n);
	}
	r += ft_print_space_memory(b, n, 1);
	return (r);
}
