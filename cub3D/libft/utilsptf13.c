/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsptf13.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvasco-m <dvasco-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 16:28:50 by dvasco-m          #+#    #+#             */
/*   Updated: 2023/01/26 20:31:28 by dvasco-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	write_ox_block_spaces(t_parms *parms, char *block, ssize_t *err)
{
	int		total_write;
	size_t	lenblock;

	lenblock = ft_strlen_ptf(block);
	total_write = 0;
	if (write(1, parms->ox, 2) != 2)
		*err = 1;
	else
	{
		if (write(1, block, lenblock) != (ssize_t)lenblock)
			*err = 1;
		else
		{
			total_write = 2 + lenblock;
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

void	print_c_zero_space(char c, int *total_write, ssize_t *err)
{
	if (write(1, &c, 1) != 1)
				*err = 1;
	else
		*total_write = *total_write + 1;
}

int	write_spaces_zeros_ox_block(t_parms *parms, char *block, ssize_t *err)
{
	int		total_write;
	size_t	lenblock;
	char	c;
	int		hollow;

	if (parms->zero && (!parms->point))
		c = '0';
	else
		c = ' ';
	total_write = 0;
	lenblock = ft_strlen_ptf(block);
	hollow = (int)(parms->width - (2 + lenblock));
	if (parms->width > (2 + lenblock))
	{
		while ((total_write < hollow) && *err == 0)
			print_c_zero_space(c, &total_write, err);
	}
	if (write(1, parms->ox, 2) != 2 || *err)
		*err = 1;
	else if ((write(1, block, lenblock) != (int)lenblock) || *err)
		*err = 1;
	else
		total_write += 2 + lenblock;
	return (total_write);
}

char	*new_block_prec(t_parms *parms, char *block, ssize_t *err)
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

char	*new_block_prec_special_0(ssize_t *err)
{
	char	*block2;

	block2 = (char *)malloc(1);
	if (block2 == NULL)
		*err = 1;
	else
		block2[0] = '\0';
	return (block2);
}
