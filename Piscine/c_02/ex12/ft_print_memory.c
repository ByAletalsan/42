/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_memory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 18:48:01 by atalaver          #+#    #+#             */
/*   Updated: 2022/07/14 12:19:27 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putnbr(unsigned long nb)
{
	if (nb > 9)
	{
		ft_putnbr(nb / 10);
		ft_putnbr(nb % 10);
	}
	else
	{
		ft_putchar(nb + '0');
	}
}

void	ft_putchar_to_hex(char c)
{
	int			operation;
	char		p;
	char		hex[2];

	p = 'a';
	operation = c % 16;
	if (operation <= 9)
		hex[1] = '0' + operation;
	else
		hex[1] = p + (operation - 10);
	operation = c / 16;
	if (operation <= 9)
		hex[0] = operation + '0';
	else
		hex[0] = p + (operation - 10);
	write(1, hex, 2);
}

void	*ft_print_memory(void *addr, unsigned int size)
{
	write(1, (addr & 0xf), 1);
	return (addr);
}
