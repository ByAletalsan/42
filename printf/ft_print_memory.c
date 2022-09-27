/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_memory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 20:06:26 by atalaver          #+#    #+#             */
/*   Updated: 2022/09/27 20:55:12 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include <stdio.h>

static int	ft_memlen(unsigned long long n)
{
	int	i;

	i = 0;
	while (n >= 16)
	{
		n /= 16;
		i++;
	}
	return (i);
}

static void	ft_print_hexchar(int n)
{
	if (n < 10)
		ft_putnbr_fd(n, 1);
	else
		ft_putchar_fd(n + 87, 1);
}

static void	ft_itemem(unsigned long long n)
{
	unsigned long i;

	i = (unsigned long)n;
	if (i >= 16)
	{
		ft_itemem(i / 16);
		ft_itemem(i % 16);
	}
	else
	{
		ft_print_hexchar(i);
	}
}

int	ft_print_memory(unsigned long long n)
{
	ft_putstr_fd("0x", 1);
	ft_itemem(n);
	return (ft_memlen(n) + 2);
}
