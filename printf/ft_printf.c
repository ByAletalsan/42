/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 10:20:47 by atalaver          #+#    #+#             */
/*   Updated: 2022/09/27 20:49:14 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int	ft_print_arg(va_list arg, char const *s)
{
	int	r;

	if (*s == '%')
		r = ft_print_char('%');
	else if (*s == 'c')
		r = ft_print_char(va_arg(arg, int));
	else if (*s == 's')
		r = ft_print_string(va_arg(arg, char *));
	else if (*s == 'i')
		r = ft_print_int(va_arg(arg, int));
	else if (*s == 'p')
		r = ft_print_memory(va_arg(arg, unsigned long long));
	return (r);
}

int	ft_printf(char const *s, ...)
{
	va_list	arg;
	int		i;
	int		count;
	int		dev;

	i = -1;
	count = 0;
	va_start(arg, s);
	while (s[++i] != '\0')
	{
		if (s[i] == '%')
		{
			dev = ft_print_arg(arg, &s[++i]);
			count += dev;
		}
		else
		{
			ft_putchar_fd(s[i], 1);
			count++;
		}
	}
	return (va_end(arg), count);
}
