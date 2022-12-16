/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 10:32:21 by atalaver          #+#    #+#             */
/*   Updated: 2022/10/27 11:40:41 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_char(char c)
{
	ft_putchar_fd(c, 1);
	return (1);
}

int	ft_print_space(t_bonus *b, int p)
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
