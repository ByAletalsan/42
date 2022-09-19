/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_comb2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 16:45:24 by atalaver          #+#    #+#             */
/*   Updated: 2022/07/11 14:45:31 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	imprimir(char c1_1, char c1_2, char c2_1, char c2_2)
{
	if (c1_1 != c2_1 || c1_2 != c2_2)
	{
		write(1, &c1_1, 1);
		write(1, &c1_2, 1);
		write(1, " ", 1);
		write(1, &c2_1, 1);
		write(1, &c2_2, 1);
		if (c1_1 != '9' || c1_2 != '8')
		{
			write(1, ", ", 2);
		}
	}
}

void	cambiar(char *a, char *b)
{
	if (*b == '9')
	{
		*b = '0';
		*a += 1;
	}
	*b += 1;
}

void	ft_print_comb2(void)
{
	char	c1_1;
	char	c1_2;
	char	c2_1;
	char	c2_2;

	c1_1 = '0';
	c1_2 = '0';
	while (c1_1 != '9' || c1_2 != '9')
	{
		c2_1 = c1_1;
		c2_2 = c1_2 + 1;
		while (c2_2 <= '9' && c2_1 <= '9')
		{
			imprimir(c1_1, c1_2, c2_1, c2_2);
			cambiar(&c2_1, &c2_2);
		}
		cambiar(&c1_1, &c1_2);
	}
}

int main(){
	ft_print_comb2();
}
