/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_string.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 21:15:13 by atalaver          #+#    #+#             */
/*   Updated: 2022/10/25 18:08:24 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_strlen_bonus(char *s, t_bonus *b)
{
	size_t	i;

	i = 0;
	if (!s && b->punto == 0)
		return (6);
	else if (!s && b->punto == 1)
		return (b->limit);
	while (s[i] != '\0')
		i++;
	return (i);
}

static void	ft_set_limit(char *s, t_bonus *b)
{
	if (b->limit > ft_strlen_bonus(s, b) && s)
		b->limit = ft_strlen_bonus(s, b);
	else if (!s && (b->limit >= 6 || b->punto == 0))
		b->limit = 6;
	else if (b->punto == 0)
		b->limit = ft_strlen_bonus(s, b);
	else if (b->limit < 0)
		b->limit = 0;
}

static int	ft_print_null(t_bonus *b)
{
	char	*s;
	int		i;
	int		r;

	i = 0;
	r = 0;
	s = ft_strdup("(null)");
	if (!b->punto)
		b->limit = 6;
	while (i < (int)ft_strlen_bonus(s, b) && i < b->limit)
		r += ft_print_char(s[i++]);
	free(s);
	return (r);
}

int	ft_print_string(char *s, t_bonus *b)
{
	int		i;
	int		r;

	i = 0;
	r = 0;
	ft_set_limit(s, b);
	r += ft_print_space(b, 0);
	if (!s)
		r += ft_print_null(b);
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
