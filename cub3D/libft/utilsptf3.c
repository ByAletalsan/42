/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsptf3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvasco-m <dvasco-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 13:45:10 by dvasco-m          #+#    #+#             */
/*   Updated: 2023/01/26 20:30:47 by dvasco-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	fill_hex_base(char *hex_base, char c)
{
	int	i;
	int	j;

	if (c == 'x')
		c = 'a';
	if (c == 'X')
		c = 'A';
	i = 0;
	while (i < 10)
	{
		hex_base[i] = '0' + i;
		i++;
	}
	j = 0;
	while (i < 16)
	{
		hex_base[i] = c + j;
		j++;
		i++;
	}
	hex_base[i] = '\0';
}

void	bld_nmb_ptf_hex(char *number, unsigned int n, int figures, char c)
{
	char		hex_base[17];
	int			i;

	fill_hex_base(hex_base, c);
	i = figures - 1;
	while (i >= 0)
	{
		number[i] = hex_base[(n % 16)];
		n = n / 16;
		i--;
	}
	number[figures] = '\0';
}

char	*ft_itoa_ptf_hex(unsigned int n, char c)
{
	char		*number;
	int			figures;

	figures = ptf_count_figures_hex(n);
	number = (char *)malloc((figures + 1) * sizeof(char));
	if (number == NULL)
		return (NULL);
	bld_nmb_ptf_hex(number, n, figures, c);
	return (number);
}

int	ptf_count_figures_ptr(unsigned long int n)
{
	int	i;

	i = 1;
	while ((n / 16) != 0)
	{
		i++;
		n = n / 16;
	}
	return (i);
}

void	fill_ptr_base(char *hex_base)
{
	int	i;
	int	j;

	i = 0;
	while (i < 10)
	{
		hex_base[i] = '0' + i;
		i++;
	}
	j = 0;
	while (i < 16)
	{
		hex_base[i] = 'a' + j;
		j++;
		i++;
	}
	hex_base[i] = '\0';
}
