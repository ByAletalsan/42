/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_comb.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 16:45:24 by atalaver          #+#    #+#             */
/*   Updated: 2022/07/09 22:03:18 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	imprimir(char c1, char c2, char c3)
{
	if (c1 != c2)
	{
		if (c1 != c3)
		{
			if (c2 != c3)
			{
				write(1, &c1, 1);
				write(1, &c2, 1);
				write(1, &c3, 1);
				if (c1 != '7' || c2 != '8' || c3 != '9')
				{
					write(1, ", ", 2);
				}
			}
		}
	}
}

void	ft_print_comb(void)
{
	char	c1;
	char	c2;
	char	c3;

	c1 = '0';
	while (c1 <= '9')
	{
		c2 = c1;
		while (c2 <= '9')
		{
			c3 = c2;
			while (c3 <= '9')
			{
				imprimir(c1, c2, c3);
				c3++;
			}
			c2++;
		}
		c1++;
	}
}
