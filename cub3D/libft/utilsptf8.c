/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsptf8.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvasco-m <dvasco-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 13:57:50 by dvasco-m          #+#    #+#             */
/*   Updated: 2023/01/26 20:31:08 by dvasco-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*fill_without_width_int(t_parms *parms, char *number, ssize_t *err)
{
	size_t	j;
	char	*block;
	size_t	pos;

	j = 0;
	if ((parms->plus || parms->space) && number[0] != '-')
		j = 1;
	block = (char *)malloc(ft_strlen_ptf(number) + j + 1);
	if (block == NULL)
	{
		*err = 1;
		return (NULL);
	}
	if (parms->plus && number[0] != '-')
		block[0] = '+';
	if (parms->space && !parms->plus && number[0] != '-')
		block[0] = ' ';
	pos = set_nmb_block(number, block, j, parms);
	block[pos] = '\0';
	return (block);
}

int	write_int(t_parms *parms, char *number, ssize_t *err)
{
	char	*block;
	int		total_write;

	if (ft_strlen_ptf(number) < parms->width)
	{
		if (parms->zero && !parms->minus)
			block = fill_w_zero_int(parms, number, err);
		else if (parms->minus)
			block = fill_minus_int(parms, number, err);
		else if (parms->space && !parms->minus && !parms->zero)
			block = fill_space_int(parms, number, err);
		else
		{
			parms->only_width = 1;
			block = fill_w_zero_int(parms, number, err);
		}
	}
	else
		block = fill_without_width_int(parms, number, err);
	if (block == NULL)
		return (0);
	total_write = write(1, block, ft_strlen_ptf(block));
	if (total_write != (int)ft_strlen_ptf(block))
		*err = 1;
	return (free (block), total_write);
}

void	fill_block_prec_zeros(size_t zeros, char *block, size_t *i)
{
	while (zeros > 0)
	{
		block[*i] = '0';
		zeros--;
		*i = *i + 1;
	}
}

void	fill_block_prc_nmb(char *number, char *block, size_t *i, size_t digits)
{
	size_t	j;

	j = 0;
	if (number[j] == '-')
		j++;
	while (digits > 0 && number[j] != '\0')
	{
		block[*i] = number[j];
		digits--;
		j++;
		*i = *i + 1;
	}
	block[*i] = '\0';
}

void	mke_special_zero(t_parms *parms, char *block)
{
	if (parms->prec == 0 && parms->num0 && !parms->plus && !parms->space)
		block[0] = '\0';
	if (parms->prec == 0 && parms->num0 && (parms->plus || parms->space))
	{
		if (parms->plus)
			block[0] = '+';
		else
			block[0] = ' ';
		block[1] = '\0';
	}
}
