/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsptf14.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvasco-m <dvasco-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 16:31:33 by dvasco-m          #+#    #+#             */
/*   Updated: 2023/01/26 20:31:31 by dvasco-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	write_ptr_prec(t_parms *parms, char *block, ssize_t *err)
{
	int		total_write;
	char	*block2;

	block2 = block;
	total_write = 0;
	if (parms->prec == 0 && parms->hex0)
		block2 = new_block_prec_special_0(err);
	else if (parms->prec > ft_strlen_ptf(block))
		block2 = new_block_prec(parms, block, err);
	if ((parms->width > ft_strlen_ptf(block)) && *err == 0)
	{
		if (parms->minus)
			total_write = write_ox_block_spaces(parms, block2, err);
		else
			total_write = write_spaces_zeros_ox_block(parms, block2, err);
	}
	else if (*err == 0)
		total_write = write_ox_block(parms, block2, err);
	if ((block2 != NULL) && (block2 != block))
		free(block2);
	return (total_write);
}

int	write_ptr_noprec(t_parms *parms, char *block, ssize_t *err)
{
	int	total_write;

	total_write = 0;
	if (parms->width > ft_strlen_ptf(block))
	{
		if (parms->minus)
			total_write = write_ox_block_spaces(parms, block, err);
		else
			total_write = write_spaces_zeros_ox_block(parms, block, err);
	}
	else
		total_write = write_ox_block(parms, block, err);
	return (total_write);
}

int	gst_and_wr_pnt(t_parms *parms, va_list ap, ssize_t *err)
{
	int		total_write;
	char	*block;

	block = p_var(ap, parms);
	if (block == NULL)
	{
		*err = 1;
		return (0);
	}
	if (parms->point)
		total_write = write_ptr_prec(parms, block, err);
	else
		total_write = write_ptr_noprec(parms, block, err);
	if (block != NULL)
		free(block);
	return (total_write);
}

int	wrhex_ox_block(t_parms *parms, char *block, ssize_t *err)
{
	int		total_write;
	size_t	lenblock;
	size_t	k;

	k = 0;
	total_write = 0;
	lenblock = ft_strlen_ptf(block);
	if (!parms->hex0 && parms->hash)
	{
		if (write(1, parms->ox, 2) != 2)
			*err = 1;
		k = 2;
	}
	if (*err == 0)
	{
		if (write(1, block, lenblock) != (int)lenblock)
			*err = 1;
		else
			total_write = k + lenblock;
	}
	return (total_write);
}

ssize_t	print_ox_hex(t_parms *parms, size_t *k)
{
	ssize_t	err;

	err = 0;
	if (parms->hash && !parms->hex0)
	{
		if (write(1, parms->ox, 2) != 2)
			err = 1;
		*k = 2;
	}
	return (err);
}
