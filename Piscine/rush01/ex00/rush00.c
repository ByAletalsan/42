/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush00.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 16:30:57 by andrgarc          #+#    #+#             */
/*   Updated: 2022/07/10 18:12:28 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_putchar(char c);

char	caracter_a_imprimir(int x, int y, int c_x, int c_y)
{
	if ((c_y == 1 && c_x == 1) || (c_y == 1 && c_x == x))
	{
		return ('o');
	}
	if ((c_y == y && c_x == 1) || (c_y == y && c_x == x))
	{
		return ('o');
	}
	if ((c_y == 1 && 1 < c_x < x) || (1 < c_x < x && c_y == y))
	{
		return ('-');
	}
	if ((c_x == 1 && 1 < c_y < y) || (1 < c_y < x && c_x == x))
	{
		return ('|');
	}
	else
	{
		return (' ');
	}
}

int	negativo(int n)
{
	if (n < 0)
	{
		return (-n);
	}
	else
	{
		return (n);
	}
}

void	rush(int x, int y)
{
	int	c_x;
	int	c_y;

	c_x = 1;
	c_y = 1;
	x = negativo(x);
	y = negativo(y);
	while (c_y <= y)
	{
		c_x = 1;
		while (c_x <= x)
		{
			ft_putchar(caracter_a_imprimir(x, y, c_x, c_y));
			c_x++;
		}
		ft_putchar('\n');
		c_y++;
	}
}
