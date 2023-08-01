/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvasco-m <dvasco-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 23:37:43 by dvasco-m          #+#    #+#             */
/*   Updated: 2022/09/28 00:22:33 by dvasco-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int		c;
	int		r;
	char	digito;

	if (n < 0)
	{
		write (fd, "-", 1);
	}
	c = n / 10;
	r = n % 10;
	if (c < 0 || r < 0)
	{
		c *= -1;
		r *= -1;
	}
	if (c != 0)
		ft_putnbr_fd(c, fd);
	digito = r + 48;
	write (fd, &digito, 1);
}
