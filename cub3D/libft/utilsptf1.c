/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsptf1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvasco-m <dvasco-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 13:40:36 by dvasco-m          #+#    #+#             */
/*   Updated: 2023/01/26 20:30:39 by dvasco-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	init_parms(t_parms	*parms)
{
	parms->hash = 0;
	parms->minus = 0;
	parms->plus = 0;
	parms->point = 0;
	parms->prec = 0;
	parms->space = 0;
	parms->width = 0;
	parms->zero = 0;
	parms->only_width = 0;
	parms->total_write = 0;
	parms->hex0 = 0;
	parms->ox[0] = '0';
	parms->ox[1] = 'x';
	parms->ox[2] = '\0';
	parms->num0 = 0;
}

size_t	ft_strlen_ptf(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0' && s != NULL)
		i++;
	return (i);
}

int	ptf_count_figures(int n)
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

void	fill_dc_base_ptf(char *dec_base)
{
	int	i;

	i = 0;
	while (i < 10)
	{
		dec_base[i] = '0' + i;
		i++;
	}
	dec_base[i] = '\0';
}

void	bld_nmb_ptf(char *number, int n, int figures, int sign)
{
	char		dec_base[11];
	int			i;
	int			orisign;

	fill_dc_base_ptf(dec_base);
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
