/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_char_string.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 10:32:21 by atalaver          #+#    #+#             */
/*   Updated: 2022/10/15 17:49:09 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_char(char c)
{
	ft_putchar_fd(c, 1);
	return (1);
}

static int	ft_print_space(t_bonus *b, int p)
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
	r += ft_print_space(b, 0);
	r += ft_print_char(c);
	r += ft_print_space(b, 1);
	return (r);
}

static int	ft_strlen_bonus(char *s, t_bonus *b)
{
	size_t	i;

	i = 0;
	if (!s && b->punto == 0)
		return (6);
	if (!s && b->punto == 1)
	{
		if (b->limit < 6)
			return (0);
		else
			return (b->limit);
	}
	while (s[i] != '\0')
		i++;
	return (i);
}


int	ft_print_string(char *s, t_bonus *b)
{
	int	i;
	int	r;

	i = 0;
	r = 0;
	if (b->limit > ft_strlen_bonus(s, b) && s)
		b->limit = ft_strlen_bonus(s, b);
	else if (!s && (b->limit >= 6 || b->punto == 0))
		b->limit = 6;
	else if (!s)
		b->limit = 0;
	else if (b->punto == 0)
		b->limit = ft_strlen_bonus(s, b);
	else if (b->limit < 0)
		b->limit = 0;
	r += ft_print_space(b, 0);
	if (!s && b->punto == 0)
	{
		ft_putstr_fd("(null)", 1);
		r += 6;
	}
	else if (!s && b->punto == 1 && b->limit >= 6)
	{
		ft_putstr_fd("(null)", 1);
		r += 6;
	}
	else if (b->punto == 1)
	{
		while (i < (int)ft_strlen_bonus(s, b) && i < b->limit)
			r += ft_print_char(s[i++]);
	}
	else if (s[0] != '\0')
	{
		ft_putstr_fd(s, 1);
		r += ft_strlen(s);
	}
	r += ft_print_space(b, 1);
	return (r);
}
