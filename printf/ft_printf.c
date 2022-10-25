/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 10:20:47 by atalaver          #+#    #+#             */
/*   Updated: 2022/10/25 18:55:19 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_print_arg(va_list arg, int option, t_bonus *b)
{
	int	r;

	r = 0;
	if (option == 8)
		r = ft_print_string("%", b);
	else if (option == 0)
		r = ft_print_char_bonus(b, va_arg(arg, int));
	else if (option == 1)
		r = ft_print_string(va_arg(arg, char *), b);
	else if (option == 4 || option == 3)
		r = ft_print_int(va_arg(arg, int), b);
	else if (option == 2)
		r = ft_print_memory(va_arg(arg, unsigned long long), b);
	else if (option == 5)
		r = ft_print_uint(va_arg(arg, unsigned int), b);
	else if (option == 6)
		r = ft_print_hexa(va_arg(arg, unsigned int), 'x', b);
	else if (option == 7)
		r = ft_print_hexa(va_arg(arg, unsigned int), 'X', b);
	return (r);
}

static void	ft_is_bonus(const char *s, int *i, t_bonus *r)
{
	char	*b;
	int		control;
	int		j;

	b = "-0.# +";
	ft_startbonus(r);
	control = 1;
	while (control)
	{
		control = 0;
		j = 0;
		while (j < 6)
		{
			if (s[*i] == b[j] || ft_isdigit(s[*i]))
			{
				ft_add_bonus(r, s, i);
				control = 1;
				break ;
			}
			j++;
		}
	}
	return ;
}

static int	ft_is_option(const char *s, int i)
{
	char	*option;
	int		j;

	option = "cspdiuxX%%";
	j = 0;
	while (option[j])
	{
		if (s[i] == option[j])
			return (j);
		j++;
	}
	return (-1);
}

static int	ft_is(char const *s, int *i, t_bonus *b)
{
	int	dev;

	ft_is_bonus(s, i, b);
	dev = ft_is_option(s, *i);
	if (dev < 0)
		free(b);
	return (dev);
}

int	ft_printf(char const *s, ...)
{
	va_list			arg;
	int				i;
	int				count;
	t_bonus			*bonus;

	i = -1;
	count = 0;
	va_start(arg, s);
	bonus = (t_bonus *)malloc(sizeof(t_bonus));
	if (!bonus)
		return (-1);
	while (s[++i] != '\0')
	{
		if (s[i] == '%')
		{
			i++;
			if (ft_is(s, &i, bonus) < 0)
				return (-1);
			count += ft_print_arg(arg, ft_is_option(s, i), bonus);
		}
		else
			count += ft_print_char(s[i]);
	}
	free(bonus);
	return (va_end(arg), count);
}
