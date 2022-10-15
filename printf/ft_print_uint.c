/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_uint.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 10:27:17 by atalaver          #+#    #+#             */
/*   Updated: 2022/10/15 19:28:58 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdlib.h>

#include <stdio.h>

static int	ft_cntchr(unsigned int n, t_bonus *b)
{
	int	i;

	i = 0;
	if (n == 0 && (b->limit > 0 || b->punto == 0))
		i++;
	while (n != 0)
	{
		i++;
		n /= 10;
	}
	return (i);
}

static char	*ft_uitoa(unsigned int n, t_bonus *b)
{
	char	*s;
	int		len;
	int		i;

	len = ft_cntchr(n, b);
	i = len;
	s = (char *)malloc(len + 1);
	if (!s)
		return (0);
	s[i] = '\0';
	while (i != 0)
	{
		s[i - 1] = (n % 10) + '0';
		n /= 10;
		i--;
	}
	return (s);
}

static int	ft_print_spaces_uint(t_bonus *b, int p)
{
	int	i;

	i = 0;
	if (b->menos == 0 && p == 0)
	{
		while (i < (b->width - b->limit))
		{
			if (b->cero == 0 || b->punto == 1)
				ft_print_char(' ');
			else
				ft_print_char('0');
			i++;
		}
	}
	if (b->menos == 1 && p == 1)
	{
		while (i < (b->width - b->limit))
		{
			ft_print_char(' ');
			i++;
		}
	}
	return (i);
}

static int	ft_print_ceros_uint(t_bonus *b, unsigned int n)
{
	int	i;

	i = 0;
	while (b->punto == 1 && i < (b->limit - ft_cntchr(n, b)))
	{
		ft_print_char('0');
		i++;
	}
	return (i);
}

int	ft_print_uint(unsigned int n, t_bonus *b)
{
	char	*s;
	int		r;

	r = 0;
	if (b->limit < ft_cntchr(n, b))
		b->limit = ft_cntchr(n, b);
	r += ft_print_spaces_uint(b, 0);
	r += ft_print_ceros_uint(b, n);
	s = ft_uitoa(n, b);
	ft_putstr_fd(s, 1);
	r += ft_strlen(s);
	r += ft_print_spaces_uint(b, 1);
	free(s);
	return (r);
}
