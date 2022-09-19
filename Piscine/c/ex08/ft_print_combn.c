/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_combn.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 15:55:54 by atalaver          #+#    #+#             */
/*   Updated: 2022/07/09 19:36:18 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<unistd.h>

void	sum(char *combo, int i, int n)
{
	combo[i++] += 1;
	while (i < n)
	{
		combo[i] = combo[i - 1] + 1;
		i++;
	}
}

int	finish(char *combo, int n)
{
	char	c;
	int		i;

	c = '9';
	i = n - 1;
	while (i >= 0)
	{
		if (combo[i] != c)
		{
			return (i);
		}
		c--;
		i--;
	}
	return (-1);
}

void	ft_print_combn(int n)
{
	char	combo[10];
	int		i;
	char	c;

	i = 0;
	c = '0';
	while (i < n)
	{
		combo[i++] = c++;
	}
	combo[i] = '\0';
	i = finish(combo, n);
	while (i != -1)
	{
		write(1, combo, n);
		write(1, ", ", 2);
		sum(combo, i, n);
		i = finish(combo, n);
	}
	write(1, combo, n);
}
