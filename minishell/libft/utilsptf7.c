/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsptf7.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvasco-m <dvasco-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 13:55:54 by dvasco-m          #+#    #+#             */
/*   Updated: 2023/01/26 20:31:05 by dvasco-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	set_nmb_block(char *number, char *block, size_t pos, t_parms *parms)
{
	size_t	i;
	size_t	first;

	first = 1;
	i = 0;
	while (i < ft_strlen_ptf(number))
	{
		if (number[0] == '-' && parms->zero && !parms->minus && first)
		{
			if (ft_strlen_ptf(number) >= parms->width)
				first = 0;
			else
			{
				block[0] = '-';
				block[pos++] = '0';
				i++;
				first = 0;
			}
		}
		block[pos] = number[i];
		i++;
		pos++;
	}
	return (pos);
}

size_t	eval_flags_space_plus(t_parms *parms, char *n, size_t *j, char *block)
{
	size_t	zeros;

	zeros = 0;
	if (parms->space && !parms->minus && !parms->plus && n[0] != '-')
	{
		block[zeros++] = ' ';
		*j = 0;
	}
	else if (!parms->minus && parms->plus && parms->zero && n[0] != '-')
	{
		block[zeros++] = '+';
		*j = 0;
	}
	while (zeros < (parms->width - ft_strlen_ptf(n)) - *j)
	{
		if (parms->only_width)
			block[zeros++] = ' ';
		else
			block[zeros++] = '0';
	}
	return (zeros);
}

char	*fill_w_zero_int(t_parms *parms, char *number, ssize_t *err)
{
	size_t	zeros;
	size_t	j;
	size_t	pos;
	char	*block;

	j = 0;
	if (parms->plus && number[0] != '-')
		j = 1;
	block = (char *)malloc(parms->width + 1 + j);
	if (block == NULL)
	{
		*err = 1;
		return (NULL);
	}
	zeros = eval_flags_space_plus(parms, number, &j, block);
	pos_plus_space(&zeros, number, block, parms);
	pos = set_nmb_block(number, block, zeros, parms);
	block[pos] = '\0';
	return (block);
}

char	*fill_minus_int(t_parms *parms, char *number, ssize_t *err)
{
	size_t	spaces;
	size_t	pos;
	char	*block;

	spaces = 0;
	block = (char *)malloc(parms->width + 1);
	if (block == NULL)
	{
		*err = 1;
		return (NULL);
	}
	pos_plus_minus(&spaces, number, block, parms);
	pos = set_nmb_block(number, block, spaces, parms);
	while (pos < parms->width)
	{
		block[pos] = ' ';
		pos++;
	}
	block[pos] = '\0';
	return (block);
}

char	*fill_space_int(t_parms *parms, char *number, ssize_t *err)
{
	size_t	zeros;
	size_t	j;
	size_t	pos;
	char	*block;

	j = 0;
	zeros = 0;
	block = (char *)malloc(parms->width + 1);
	if (block == NULL)
	{
		*err = 1;
		return (NULL);
	}
	if ((parms->plus || parms->space) && number[0] != '-')
		j = 1;
	while (zeros < (parms->width - ft_strlen_ptf(number) - j))
	{
		block[zeros] = ' ';
		zeros++;
	}
	pos_plus_space(&zeros, number, block, parms);
	pos = set_nmb_block(number, block, zeros, parms);
	block[pos] = '\0';
	return (block);
}
