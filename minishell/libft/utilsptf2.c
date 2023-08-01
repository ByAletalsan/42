/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsptf2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvasco-m <dvasco-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 13:44:02 by dvasco-m          #+#    #+#             */
/*   Updated: 2023/01/26 20:30:43 by dvasco-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa_ptf(int n)
{
	char		*number;
	int			figures;
	int			sign;

	sign = 0;
	figures = ptf_count_figures(n);
	if (n < 0)
		sign = 1;
	number = (char *)malloc((figures + sign + 1) * sizeof(char));
	if (number == NULL)
		return (NULL);
	bld_nmb_ptf(number, n, figures, sign);
	return (number);
}

int	ptf_count_figures_u(unsigned int n)
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

void	bld_nmb_ptf_u(char *number, unsigned int n, int figures)
{
	char		dec_base[11];
	int			i;

	fill_dc_base_ptf(dec_base);
	i = figures - 1;
	while (i >= 0)
	{
		number[i] = dec_base[n % 10];
		n = n / 10;
		i--;
	}
	number[figures] = '\0';
}

char	*ft_uitoa(unsigned int n)
{
	char		*number;
	int			figures;

	figures = ptf_count_figures_u(n);
	number = (char *)malloc((figures + 1) * sizeof(char));
	if (number == NULL)
		return (NULL);
	bld_nmb_ptf_u(number, n, figures);
	return (number);
}

int	ptf_count_figures_hex(unsigned int n)
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
