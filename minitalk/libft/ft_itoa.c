/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 10:02:18 by atalaver          #+#    #+#             */
/*   Updated: 2022/09/22 12:04:17 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_cntchr(int n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		i++;
	while (n != 0)
	{
		i++;
		n /= 10;
	}
	return (i);
}

static	char	ft_poschr(int n)
{
	if (n < 0)
		return ((n % 10) * -1);
	else
		return (n % 10);
}

char	*ft_itoa(int n)
{
	char	*s;
	size_t	len;
	size_t	i;
	int		neg;

	len = ft_cntchr(n);
	i = len;
	neg = 0;
	if (n < 0)
		neg = 1;
	s = (char *)malloc(len + 1);
	if (!s)
		return (NULL);
	s[i--] = '\0';
	while (i > 0)
	{
		s[i] = ft_poschr(n) + '0';
		n /= 10;
		i--;
	}
	if (neg)
		s[i] = '-';
	else
		s[i] = n + '0';
	return (s);
}
