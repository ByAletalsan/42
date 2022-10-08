/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 11:13:48 by atalaver          #+#    #+#             */
/*   Updated: 2022/10/08 12:04:28 by atalaver         ###   ########.fr       */
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

int	ft_print_hexa(unsigned int n, char format)
{
	if (n == 0)
		return (write(1, "0", 1));
	else
		ft_itemem(n, format);
	return (ft_memlen(n));
}
