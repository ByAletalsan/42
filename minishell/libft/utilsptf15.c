/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsptf15.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvasco-m <dvasco-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 16:35:49 by dvasco-m          #+#    #+#             */
/*   Updated: 2023/01/26 20:31:36 by dvasco-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	wrhex_ox_block_spaces(t_parms *parms, char *block, ssize_t *err)
{
	int		total_write;
	size_t	k;

	k = 0;
	total_write = 0;
	if (parms->hash && !parms->hex0)
		*err = print_ox_hex(parms, &k);
	if (*err == 0)
	{
		if (write(1, block, ft_strlen_ptf(block)) != (int)ft_strlen_ptf(block))
			*err = 1;
		else
		{
			total_write = k + ft_strlen_ptf(block);
			while ((total_write < (int)parms->width) && *err == 0)
			{
				if (write(1, " ", 1) != 1)
					*err = 1;
				total_write++;
			}
		}
	}
	return (total_write);
}

int	print_zero_space(t_parms *parms, char c, size_t hollow, ssize_t *err)
{
	int	total_write;

	total_write = 0;
	if (parms->width > hollow)
	{
		while ((total_write < (int)(parms->width - hollow)) && *err == 0)
		{
			if (write(1, &c, 1) != 1)
				*err = 1;
			else
				total_write++;
		}
	}
	return (total_write);
}

ssize_t	print_ox(t_parms *parms, size_t *k)
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

int	wrhex_spaces_zeros_ox_block(t_parms *parms, char *block, ssize_t *err)
{
	int		total_write;
	size_t	lenblock;
	char	c;
	size_t	k;

	if (parms->zero && (!parms->point))
		c = '0';
	else
		c = ' ';
	k = 0;
	if (parms->hash && !parms->hex0)
		k = 2;
	if (parms->zero && !parms->prec)
		*err = print_ox(parms, &k);
	lenblock = ft_strlen_ptf(block);
	total_write = print_zero_space(parms, c, (k + lenblock), err);
	if (parms->hash && !parms->zero)
		*err = print_ox(parms, &k);
	if ((write(1, block, lenblock) != (int)lenblock) || *err)
		*err = 1;
	total_write += k + lenblock;
	return (total_write);
}

char	*new_block_hx_prec(t_parms *parms, char *block, ssize_t *err)
{
	char	*block2;
	size_t	i;
	size_t	j;
	size_t	lenblock;

	block2 = (char *)malloc(parms->prec + 1);
	if (block2 == NULL)
		*err = 1;
	else
	{
		i = 0;
		lenblock = ft_strlen_ptf(block);
		while (i < (parms->prec - lenblock))
			block2[i++] = '0';
		j = 0;
		while (j < lenblock)
			block2[i++] = block[j++];
		block2[i] = '\0';
	}
	return (block2);
}
