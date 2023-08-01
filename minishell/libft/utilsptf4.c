/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsptf4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvasco-m <dvasco-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 13:46:13 by dvasco-m          #+#    #+#             */
/*   Updated: 2023/01/26 20:30:51 by dvasco-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	bld_nmb_ptf_ptr(char *number, unsigned long int n, int figures)
{
	char		hex_base[17];
	int			i;

	fill_ptr_base(hex_base);
	i = figures - 1;
	while (i >= 0)
	{
		number[i] = hex_base[(n % 16)];
		n = n / 16;
		i--;
	}
	number[figures] = '\0';
}

char	*ft_itoa_ptf_ptr(unsigned long int n)
{
	char		*number;
	int			figures;

	figures = ptf_count_figures_ptr(n);
	number = (char *)malloc((figures + 1) * sizeof(char));
	if (number == NULL)
		return (NULL);
	bld_nmb_ptf_ptr(number, n, figures);
	return (number);
}

char	*i_d_var(va_list ap, t_parms *parms)
{
	int	var;

	var = va_arg(ap, int);
	if (var == 0)
		parms->num0 = 1;
	return (ft_itoa_ptf(var));
}

char	*u_var(va_list ap, t_parms *parms)
{
	unsigned int	var;

	var = va_arg(ap, unsigned int);
	if (var == 0)
		parms->num0 = 1;
	parms->space = 0;
	parms->plus = 0;
	return (ft_uitoa(var));
}

char	c_var(va_list ap)
{
	char	c;

	c = va_arg(ap, int);
	return (c);
}
