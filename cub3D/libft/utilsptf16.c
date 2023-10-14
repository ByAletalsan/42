/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsptf16.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvasco-m <dvasco-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 16:37:15 by dvasco-m          #+#    #+#             */
/*   Updated: 2023/01/26 20:31:46 by dvasco-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*new_block_hx_prec_special_0(ssize_t *err, t_parms *parms)
{
	char	*block2;

	if (parms->width == 1 && parms->point && parms->prec == 0)
	{
		block2 = (char *)malloc(2);
		if (block2 == NULL)
			*err = 1;
		else
		{
			block2[0] = ' ';
			block2[1] = '\0';
		}
	}
	else
	{
		block2 = (char *)malloc(1);
		if (block2 == NULL)
			*err = 1;
		else
			block2[0] = '\0';
	}
	return (block2);
}

int	write_hex_prec(t_parms *parms, char *block, ssize_t *err, char term)
{
	int		total_write;
	char	*block2;

	block2 = block;
	total_write = 0;
	if (term == 'X')
		parms->ox[1] = 'X';
	if (parms->prec == 0 && parms->hex0)
		block2 = new_block_hx_prec_special_0(err, parms);
	else if (parms->prec > ft_strlen_ptf(block))
		block2 = new_block_hx_prec(parms, block, err);
	if ((parms->width > ft_strlen_ptf(block)) && *err == 0)
	{
		if (parms->minus)
			total_write = wrhex_ox_block_spaces(parms, block2, err);
		else
			total_write = wrhex_pr_spcs_zeros_ox_block(parms, block2, err);
	}
	else if (*err == 0)
		total_write = wrhex_ox_block(parms, block2, err);
	if ((block2 != NULL) && (block2 != block))
		free(block2);
	return (total_write);
}

int	write_hex_noprec(t_parms *parms, char *block, ssize_t *err, char term)
{
	int	total_write;

	total_write = 0;
	if (term == 'X')
		parms->ox[1] = 'X';
	if (parms->width > ft_strlen_ptf(block))
	{
		if (parms->minus)
			total_write = wrhex_ox_block_spaces(parms, block, err);
		else
			total_write = wrhex_spaces_zeros_ox_block(parms, block, err);
	}
	else
		total_write = wrhex_ox_block(parms, block, err);
	return (total_write);
}

int	gst_and_wr_hex(t_parms *parms, va_list ap, ssize_t *err, char term)
{
	int		total_write;
	char	*block;

	total_write = 0;
	block = x_var(ap, term, parms);
	if (block == NULL)
	{
		*err = 1;
		return (0);
	}
	if (parms->point)
		total_write = write_hex_prec(parms, block, err, term);
	else
		total_write = write_hex_noprec(parms, block, err, term);
	if (block != NULL)
		free(block);
	return (total_write);
}

int	gestor_args(char **start, char term, va_list ap, ssize_t *err)
{
	t_parms	parms;

	init_parms(&parms);
	analize_flags(&parms, start);
	parms.width = set_width(start, 0);
	parms.prec = set_prec(start, 0, &parms);
	if (term == 'i' || term == 'd')
		parms.total_write = gst_and_write_int(&parms, ap, err, 1);
	if (term == 'c' || term == '%')
		parms.total_write = gst_and_wr_chr(&parms, ap, err, term);
	if (term == 's')
		parms.total_write = gestor_and_write_str(&parms, ap, err);
	if (term == 'p')
		parms.total_write = gst_and_wr_pnt(&parms, ap, err);
	if (term == 'u')
		parms.total_write = gst_and_write_int(&parms, ap, err, 2);
	if (term == 'x' || term == 'X')
			parms.total_write = gst_and_wr_hex(&parms, ap, err, term);
	return (parms.total_write);
}
