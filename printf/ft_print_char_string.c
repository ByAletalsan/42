/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_char_string.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 10:32:21 by atalaver          #+#    #+#             */
/*   Updated: 2022/10/10 21:03:12 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_char(char c)
{
	ft_putchar_fd(c, 1);
	return (1);
}

static int	ft_print_spaces(t_bonus *b, int p)
{
	int	i;

	i = 0;
	if (b->menos == p)
	{
		while (i < (b->width - b->limit))
		{
			ft_print_char(' ');
			i++;
		}
	}
	return (i);
}

int	ft_print_char_bonus(t_bonus *b, char c)
{
	int	r;

	r = 0;
	b->limit = 1;
	r += ft_print_spaces(b, 0);
	r += ft_print_char(c);
	r += ft_print_spaces(b, 1);
	return (r);
}

int	ft_print_string(char *s, t_bonus *b)
{
	int	i;
	int	r;

	if (!s)
	{
		ft_putstr_fd("(null)", 1);
		return (6);
	}
	if (b->limit < 0)
		b->limit = ft_strlen(s);
	i = 0;
	r = 0;
	r += ft_print_spaces(b, 0);
	if (b->punto && s[0] != '\0')
	{
		while (i < (int)ft_strlen(s) && i < b->limit)
			r += ft_print_char(s[i++]);
	}
	else if (s[0] != '\0')
	{
		ft_putstr_fd(s, 1);
		r += b->limit;
	}
	r += ft_print_spaces(b, 1);
	return (r);
}
