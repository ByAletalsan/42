/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsptf12.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvasco-m <dvasco-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 14:03:45 by dvasco-m          #+#    #+#             */
/*   Updated: 2023/01/26 20:31:24 by dvasco-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	write_block_w(char *block, t_parms *parms, ssize_t *err)
{
	int		total_write;
	int		i;
	size_t	len_block;

	len_block = ft_strlen_ptf(block);
	total_write = 0;
	i = 0;
	if (parms->width > (len_block))
	{
		while ((i < (int)(parms->width - len_block)) && *err == 0)
		{
			if (write(1, " ", 1) != 1)
				*err = 1;
			i++;
		}
		total_write = write(1, block, len_block);
		if (total_write != (int)(len_block))
			*err = 1;
	}
	else
		total_write = write_str(block, err);
	return (total_write + i);
}

int	write_str_w(char *block, t_parms *parms, ssize_t *err)
{
	int		total_write;
	size_t	len_block;

	total_write = 0;
	len_block = ft_strlen_ptf(block);
	if (parms->width)
	{
		if (parms->minus)
			total_write = write_block_w_m(block, parms, err);
		else
		{
			if (parms->zero)
				total_write = write_block_w_0(block, parms, err);
			else
				total_write = write_block_w(block, parms, err);
		}
	}
	else
	{
		total_write = write(1, block, len_block);
		if (total_write != (int)len_block)
			*err = 1;
	}
	return (total_write);
}

char	*block_str_prec(char *str, t_parms *parms, ssize_t *err)
{
	char	*block;
	size_t	i;

	block = NULL;
	block = (char *)malloc(parms->prec + 1);
	if (block == NULL)
		*err = 1;
	else
	{
		i = 0;
		while (i < parms->prec)
		{
			block[i] = str[i];
			i++;
		}
		block[i] = '\0';
	}
	return (block);
}

int	gestor_and_write_str(t_parms *parms, va_list ap, ssize_t *err)
{
	int		total_write;
	char	*str;
	char	*block;

	block = NULL;
	total_write = 0;
	str = s_var(ap);
	if (str == NULL)
		str = "(null)";
	if (!parms->width && !parms->point)
		total_write = write_str(str, err);
	else
	{
		if (parms->point && parms->prec < ft_strlen_ptf(str))
		{
			block = block_str_prec(str, parms, err);
			if (*err == 0)
					total_write = write_str_w(block, parms, err);
		}
		else
			total_write = write_str_w(str, parms, err);
	}
	if (block != NULL)
		free(block);
	return (total_write);
}

int	write_ox_block(t_parms *parms, char *block, ssize_t *err)
{
	int		total_write;
	size_t	lenblock;

	total_write = 0;
	lenblock = ft_strlen_ptf(block);
	if (write(1, parms->ox, 2) != 2)
		*err = 1;
	else
	{
		if (write(1, block, lenblock) != (ssize_t)lenblock)
			*err = 1;
		else
			total_write = 2 + lenblock;
	}
	return (total_write);
}
