/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 10:20:47 by atalaver          #+#    #+#             */
/*   Updated: 2022/10/10 20:33:35 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdlib.h>

static int	ft_print_arg(va_list arg, int option, t_bonus *b)
{
	int	r;

	if (option == 8)
		r = ft_print_char('%');
	else if (option == 0)
		r = ft_print_char_bonus(b, va_arg(arg, int));
	else if (option == 1)
		r = ft_print_string(va_arg(arg, char *), b);
	else if (option == 4 || option == 3)
		r = ft_print_int(va_arg(arg, int));
	else if (option == 2)
		r = ft_print_memory(va_arg(arg, unsigned long long));
	else if (option == 5)
		r = ft_print_uint(va_arg(arg, unsigned int), b);
	else if (option == 6)
		r = ft_print_hexa(va_arg(arg, unsigned int), 'x');
	else if (option == 7)
		r = ft_print_hexa(va_arg(arg, unsigned int), 'X');
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
		while (j < 5)
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

int	ft_printf(char const *s, ...)
{
	va_list			arg;
	int				i;
	int				count;
	int				dev;
	t_bonus			*bonus; //Donde guardamos los bonus

	i = -1;
	count = 0;
	va_start(arg, s);
	bonus = (t_bonus *)malloc(sizeof(t_bonus));
	if (!bonus)
		return (0);
	while (s[++i] != '\0')
	{
		if (s[i] == '%')
		{
			i++;
			ft_is_bonus(s, &i, bonus); //Recogemos los bonus
			//ft_print_bonus(bonus);
			dev = ft_is_option(s, i);
			if (dev < 0)
			{
				free(bonus);
				return (dev);
			}
			count += ft_print_arg(arg, dev, bonus);
		}
		else
		{
			ft_putchar_fd(s[i], 1);
			count++;
		}
	}
	free(bonus);
	return (va_end(arg), count);
}
