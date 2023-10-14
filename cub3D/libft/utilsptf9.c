/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsptf9.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvasco-m <dvasco-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 13:59:04 by dvasco-m          #+#    #+#             */
/*   Updated: 2023/01/26 20:31:12 by dvasco-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	mke_prc_blk(t_parms *parms, char *number, size_t digits, char *block)
{
	size_t	zeros;
	size_t	i;

	i = 0;
	if (parms->prec == 0 && parms->num0)
		mke_special_zero(parms, block);
	else
	{
		if (parms->prec <= digits)
			zeros = 0;
		else
			zeros = parms->prec - digits;
		if (number[0] == '-')
				block[i++] = '-';
		else
		{
			if (parms->plus)
				block[i++] = '+';
			if (parms->space && !parms->plus)
				block[i++] = ' ';
		}
		if (parms->prec > digits)
			fill_block_prec_zeros(zeros, block, &i);
		fill_block_prc_nmb(number, block, &i, digits);
	}
}

char	*create_special_zero_block(t_parms *parms)
{
	char	*block;

	block = NULL;
	if (parms->prec == 0 && parms->num0 && !parms->plus && !parms->space)
		block = (char *)malloc(1);
	if (parms->prec == 0 && parms->num0 && (parms->plus || parms->space))
		block = (char *)malloc(2);
	return (block);
}

char	*fill_prec_int(t_parms *parms, char *number, ssize_t *err)
{
	char	*block;
	size_t	digits;
	size_t	j;

	j = 0;
	digits = ft_strlen_ptf(number);
	if (parms->prec == 0 && parms->num0)
		block = create_special_zero_block(parms);
	else
	{
		if (number[0] == '-')
			digits -= 1;
		if (parms->space || parms->plus || number[0] == '-')
				j = 1;
		if (parms->prec > digits)
			block = (char *)malloc(parms->prec + j + 1);
		else
			block = (char *)malloc(digits + j + 1);
	}
	if (block == NULL)
		*err = 1;
	else
		mke_prc_blk(parms, number, digits, block);
	return (block);
}

char	*fill_prc_wd_l(char *block, char *aux, t_parms *parms, size_t szblck)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < (parms->width - szblck))
	{
		block[i] = ' ';
		i++;
	}
	j = 0;
	while (aux[j] != '\0')
	{
		block[i] = aux[j];
		i++;
		j++;
	}
	block[i] = '\0';
	return (block);
}

char	*fill_prc_wd_r(char *block, char *aux, t_parms *parms)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (aux[j] != '\0')
	{
		block[i] = aux[j];
		i++;
		j++;
	}
	while (i < parms->width)
	{
		block[i] = ' ';
		i++;
	}
	block[i] = '\0';
	return (block);
}
