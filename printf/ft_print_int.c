/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_int.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 11:12:30 by atalaver          #+#    #+#             */
/*   Updated: 2022/10/13 12:07:59 by atalaver         ###   ########.fr       */
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

static int	ft_print_bon(t_bonus *b, int n)
{
	int	r;
	int	i;

	r = 0;
	if (n < 0)
		write(1, "-", 1);
	if (b->mas == 1 && n >= 0)
		write(1, "+", 1);
	else if (b->espacio == 1 && n >= 0)
		write(1, " ", 1);
	i = 0;
	if (n < 0)
		i = 1;
	while (r < (b->limit - (ft_count_digit(n) - i)) && b->punto == 1)
		r += ft_print_char('0');
	while (r < (b->width - (ft_count_digit(n) - i))
		&& b->cero == 1 && b->menos == 0)
		r += ft_print_char('0');
	return (r);
}

static int	ft_putnbr(int n, t_bonus *b)
{
	int		i;
	char	c;
	int		r;

	r = 0;
	i = 0;
	r += ft_print_bon(b, n);
	if (n == -2147483648)
	{
		r += write(1, "2147483648", 10);
		return (r);
	}
	if (n < 0)
		n *= -1;
	i = 0;
	while (i < ft_count_digit(n))
	{
		c = ((n / ft_pow(10, ft_count_digit(n) - (i + 1))) % 10) + '0';
		write(1, &c, 1);
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
	if (n >= 0 && (b->mas == 1 || b->espacio == 1) && b->menos == 0)
		b->width -= 1;
	r += ft_print_spaces_int(b, 0);
	r += ft_putnbr(n, b);
	r += ft_print_spaces_int(b, 1);
	if (n < 0 || b->mas == 1 || b->espacio == 1)
		return (r + 1);
	else
		return (r);
}
