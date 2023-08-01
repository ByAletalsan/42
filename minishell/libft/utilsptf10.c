/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsptf10.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvasco-m <dvasco-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 14:00:47 by dvasco-m          #+#    #+#             */
/*   Updated: 2023/01/26 20:31:16 by dvasco-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*fill_prc_wd(char *block, t_parms *parms, ssize_t *err, size_t szblck)
{
	char	*aux;

	aux = block;
	block = (char *)malloc(parms->width + 1);
	if (block == NULL)
		*err = 1;
	else
	{
		if (!parms->minus)
			block = fill_prc_wd_l(block, aux, parms, szblck);
		else
			block = fill_prc_wd_r(block, aux, parms);
		free(aux);
	}
	return (block);
}

int	write_int_prec(t_parms *parms, char *number, ssize_t *err)
{
	char	*block;
	int		total_write;
	size_t	szblck;

	total_write = 0;
	block = fill_prec_int(parms, number, err);
	if (block == NULL)
		return (total_write);
	szblck = ft_strlen_ptf(block);
	if (parms->width > szblck)
		block = fill_prc_wd(block, parms, err, szblck);
	if (block == NULL)
		return (total_write);
	szblck = ft_strlen_ptf(block);
	total_write = write(1, block, szblck);
	if (total_write != (int)szblck)
		*err = 1;
	free (block);
	return (total_write);
}

int	gst_and_write_int(t_parms *parms, va_list ap, ssize_t *err, ssize_t tp)
{
	int		total_write;
	char	*number;

	total_write = 0;
	if (tp == 1)
		number = i_d_var(ap, parms);
	if (tp == 2)
		number = u_var(ap, parms);
	if (number == NULL)
	{
		*err = 1;
		return (total_write);
	}
	if (!parms->point)
		total_write = write_int(parms, number, err);
	else
		total_write = write_int_prec(parms, number, err);
	free(number);
	return (total_write);
}

int	write_char_minus_w(char c, t_parms *parms, ssize_t *err)
{
	char	*block;
	int		total_write;
	size_t	i;

	total_write = 0;
	block = (char *)malloc(parms->width);
	if (block == NULL)
	{
		*err = 1;
		return (total_write);
	}
	if (write(1, &c, 1) != 1)
	{
		*err = 1;
		return (total_write);
	}
	i = 0;
	while (i < parms->width - 1)
		block[i++] = ' ';
	block[i] = '\0';
	total_write = write(1, block, ft_strlen_ptf(block));
	if (total_write != (int)ft_strlen_ptf(block))
		*err = 1;
	free(block);
	return (total_write + 1);
}

void	fill_zeros_spaces_char(t_parms *parms, char *block, size_t *i)
{
	while (*i < parms->width - 1)
	{
		if (parms->zero)
			block[*i] = '0';
		else
			block[*i] = ' ';
		*i = *i + 1;
	}
}
