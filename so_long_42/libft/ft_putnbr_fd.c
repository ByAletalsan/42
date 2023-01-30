/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 10:09:34 by atalaver          #+#    #+#             */
/*   Updated: 2022/09/23 18:24:13 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_digit(int n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		i++;
		n /= 10;
	}
	return (i);
}

static int	ft_pow(int b, int e)
{
	int	i;
	int	r;

	r = 1;
	i = 0;
	while (i < e)
	{
		r *= b;
		i++;
	}
	return (r);
}

void	ft_putnbr_fd(int n, int fd)
{
	size_t	i;
	char	c;

	i = 0;
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		n *= -1;
	}
	while (i < ft_count_digit(n))
	{
		c = ((n / ft_pow(10, ft_count_digit(n) - (i + 1))) % 10) + '0';
		write(fd, &c, 1);
		i++;
	}
	return ;
}
