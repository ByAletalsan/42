/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_uint.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 10:27:17 by atalaver          #+#    #+#             */
/*   Updated: 2022/10/08 12:26:00 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdlib.h>

static size_t	ft_cntchr(unsigned int n)
{
	size_t	i;

	i = 0;
	while (n != 0)
	{
		i++;
		n /= 10;
	}
	return (i);
}

static char	*ft_uitoa(unsigned int n)
{
	char	*s;
	size_t	len;
	size_t	i;

	len = ft_cntchr(n);
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

int	ft_print_uint(unsigned int n)
{
	char	*s;
	int		r;

	if (n == 0)
		return (write(1, "0", 1));
	s = ft_uitoa(n);
	r = ft_print_string(s);
	free(s);
	return (r);
}
