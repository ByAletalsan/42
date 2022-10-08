/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_memory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 20:06:26 by atalaver          #+#    #+#             */
/*   Updated: 2022/10/08 11:19:59 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_memlen(unsigned long long n)
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

int	ft_print_memory(unsigned long long n)
{
	int	print_length;

	print_length = 0;
	if (n == 0)
		print_length += write(1, "(nil)", 5);
	else
	{
		print_length += write(1, "0x", 2);
		ft_itemem(n);
		print_length += ft_memlen(n);
	}
	return (print_length);
}
