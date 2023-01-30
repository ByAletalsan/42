/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 19:48:11 by atalaver          #+#    #+#             */
/*   Updated: 2022/10/27 11:40:37 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memlen(unsigned int n, t_bonus *b)
{
	int	i;

	i = 0;
	if (n == 0 && (b->limit > 0 || b->punto == 0))
		i++;
	while (n != 0)
	{
		i++;
		n = n / 16;
	}
	return (i);
}

int	ft_print_space_memory(t_bonus *b, unsigned long long n, int p)
{
	int	i;

	i = 0;
	if (b->menos == 0 && (b->cero == 0 || n == 0) && p == 0)
	{
		while (i < (b->width - (b->limit + 2)))
		{
			ft_print_char(' ');
			i++;
		}
	}
	if (b->menos == 1 && p == 1)
	{
		while (i < (b->width - (b->limit + 2)))
		{
			ft_print_char(' ');
			i++;
		}
	}
	return (i);
}

int	ft_print_ceros(t_bonus *b, int n)
{
	int	i;

	i = 0;
	if ((b->cero == 1 && b->menos == 0) || b->punto == 1)
	{
		while (i < (b->limit - n))
		{
			ft_print_char('0');
			i++;
		}
	}
	return (i);
}

int	ft_print_spaces_int(t_bonus *b, int p)
{
	int	i;

	i = 0;
	if (b->menos == 0 && p == 0 && (b->cero == 0 || b->punto == 1))
	{
		while (i < (b->width - b->limit))
		{
			ft_print_char(' ');
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

int	ft_print_ceros_hex(t_bonus *b, unsigned int n)
{
	int	i;
	int	len;

	i = 0;
	len = ft_memlen(n, b);
	if (n != 0)
		len += b->almoadilla * 2;
	if ((b->cero == 1 && b->menos == 0) || b->punto == 1)
	{
		while (i < (b->limit - len))
		{
			ft_print_char('0');
			i++;
		}
	}
	if ((b->cero == 1 && b->menos == 0) && b->punto == 0 && b->almoadilla == 1)
	{
		while (i < (b->width - b->limit))
		{
			ft_print_char('0');
			i++;
		}
	}
	return (i);
}
