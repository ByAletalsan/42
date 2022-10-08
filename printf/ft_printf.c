/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 10:20:47 by atalaver          #+#    #+#             */
/*   Updated: 2022/10/08 12:05:48 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_print_arg(va_list arg, int option)
{
	int	r;

	if (option == 8)
		r = ft_print_char('%');
	else if (option == 0)
		r = ft_print_char(va_arg(arg, int));
	else if (option == 1)
		r = ft_print_string(va_arg(arg, char *));
	else if (option == 4 || option == 3)
		r = ft_print_int(va_arg(arg, int));
	else if (option == 2)
		r = ft_print_memory(va_arg(arg, unsigned long long));
	else if (option == 5)
		r = ft_print_uint(va_arg(arg, unsigned int));
	else if (option == 6)
		r = ft_print_hexa(va_arg(arg, unsigned int), 'x');
	else if (option == 7)
		r = ft_print_hexa(va_arg(arg, unsigned int), 'X');
	return (r);
}

/*static int	ft_is_bonus(const char *s, int *i)
{
	char	*b_1;

	b_1 = "-0.";
	if (ft_strncmp(&s[*i], b_1, 3) == 0 && s[*i + 3] == 'i')
	{
		*i += 4;
		return (9);
	}
	return (-1);
}*/

static int	ft_is_option(const char *s, int *i)
{
	char	*option;
	int		j;

	option = "cspdiuxX%%";
	j = 0;
	while (option[j])
	{
		if (s[*i] == option[j])
			return (j);
		j++;
	}
	return (-1);
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
			i++;
			dev = ft_is_option(s, &i);
			if (dev < 0)
				return (dev);
			count += ft_print_arg(arg, dev);
		}
		else
		{
			ft_putchar_fd(s[i], 1);
			count++;
		}
	}
	return (va_end(arg), count);
}
