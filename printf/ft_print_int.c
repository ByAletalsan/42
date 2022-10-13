/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_int.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 11:12:30 by atalaver          #+#    #+#             */
/*   Updated: 2022/10/12 21:27:29 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_count_digit(int n)
{
	int	i;

	i = 0;
	if (n <= 0)
		i++;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static int	ft_pow(int b, int e)
{
	int	i;
	int	r;

	r = 1;
	i = 0;
	while (i < e)
	{
		r *= b;
		i++;
	}
	return (r);
}

int	ft_putnbr(int n, int fd, t_bonus *b)
{
	int		i;
	char	c;
	int		r;

	i = 0;
	if (n < 0)
	{
		write(fd, "-", 1);
		n *= -1;
	}
	r = 0;
	while (r < (b->limit - ft_count_digit(n)) && b->punto == 1)
		r += ft_print_char('0');
	while (r < (b->width - ft_count_digit(n)) && b->cero == 1 && b->menos == 0)
		r += ft_print_char('0');
	if (n == -2147483648)
	{
		r += write(fd, "2147483648", 10);
		return (r);
	}
	while (i < ft_count_digit(n))
	{
		c = ((n / ft_pow(10, ft_count_digit(n) - (i + 1))) % 10) + '0';
		write(fd, &c, 1);
		i++;
	}
	return (i + r);
}

int	ft_print_int(int n, t_bonus *b)
{
	int	r;

	r = 0;
	if (b->limit < ft_count_digit(n) && b->punto == 0)
		b->limit = ft_count_digit(n);
	if (n < 0 && (b->cero == 1 || b->punto == 1) && b->menos == 0)
		b->width -= 1;
	r += ft_print_spaces_int(b, 0);
	r += ft_putnbr(n, 1, b);
	r += ft_print_spaces_int(b, 1);
	if (n < 0)
		return (r + 1);
	else
		return (r);
}
