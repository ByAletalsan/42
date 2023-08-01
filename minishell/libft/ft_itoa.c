/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvasco-m <dvasco-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 19:17:43 by dvasco-m          #+#    #+#             */
/*   Updated: 2023/06/22 14:35:45 by dvasco-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	count_figures(int n)
{
	int	i;

	i = 1;
	while ((n / 10) != 0)
	{
		i++;
		n = n / 10;
	}
	return (i);
}

static	void	fill_dec_base(char *dec_base)
{
	int	i;

	i = 0;
	while (i < 10)
	{
		dec_base[i] = '0' + i;
		i++;
	}
}

static	void	build_number(char *number, int n, int figures, int sign)
{
	char		dec_base[10];
	int			i;
	int			orisign;

	fill_dec_base(dec_base);
	i = figures + sign - 1;
	orisign = sign;
	if (sign == 1)
	{
		number[0] = '-';
		sign = -1;
	}
	else
		sign = 1;
	while (i >= orisign)
	{
		number[i] = dec_base[(n % 10) * sign];
		n = n / 10;
		i--;
	}
	number[figures + orisign] = '\0';
}

char	*ft_itoa(int n)
{
	char		*number;
	int			figures;
	int			sign;

	sign = 0;
	figures = count_figures(n);
	if (n < 0)
		sign = 1;
	number = (char *)malloc((figures + sign + 1) * sizeof(char));
	if (number == NULL)
		return (NULL);
	build_number(number, n, figures, sign);
	return (number);
}
