/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_struct_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 12:59:27 by atalaver          #+#    #+#             */
/*   Updated: 2022/10/27 11:41:21 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_startbonus(t_bonus *b)
{
	b->almoadilla = 0;
	b->cero = 0;
	b->espacio = 0;
	b->mas = 0;
	b->menos = 0;
	b->punto = 0;
	b->width = 0;
	b->limit = -1;
	return ;
}

static void	ft_read_number(t_bonus *b, const char *s, int *i, int option)
{
	if (option == 1)
	{
		b->punto = 1;
		b->limit = 0;
		*i += 1;
		while (ft_isdigit(s[*i]))
		{
			b->limit *= 10;
			b->limit += s[*i] - '0';
			*i += 1;
		}
	}
	else
	{
		while (ft_isdigit(s[*i]))
		{
			b->width *= 10;
			b->width += s[*i] - '0';
			*i += 1;
		}
	}
	*i -= 1;
}

void	ft_add_bonus(t_bonus *b, const char *s, int *i)
{
	if (s[*i] == '-')
		b->menos = 1;
	if (s[*i] == ' ')
		b->espacio = 1;
	if (s[*i] == '#')
		b->almoadilla = 1;
	if (s[*i] == '+')
		b->mas = 1;
	if (s[*i] == '.')
		ft_read_number(b, s, i, 1);
	else if (ft_isdigit(s[*i]))
	{
		if (s[*i] == '0')
		{
			b->cero = 1;
			*i += 1;
		}
		ft_read_number(b, s, i, 2);
	}
	*i += 1;
	return ;
}
