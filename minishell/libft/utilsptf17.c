/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsptf17.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvasco-m <dvasco-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 16:40:17 by dvasco-m          #+#    #+#             */
/*   Updated: 2023/01/26 20:31:51 by dvasco-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	wrhex_pr_spcs_zeros_ox_block(t_parms *parms, char *block, ssize_t *err)
{
	int		total_write;
	size_t	lenblock;
	char	c;
	size_t	k;

	c = ' ';
	k = 0;
	if (parms->hash && !parms->hex0)
		k = 2;
	lenblock = ft_strlen_ptf(block);
	total_write = print_zero_space(parms, c, (k + lenblock), err);
	if (parms->hash)
		*err = print_ox(parms, &k);
	if ((write(1, block, lenblock) != (int)lenblock) || *err)
		*err = 1;
	total_write += k + lenblock;
	return (total_write);
}

int	walk_and_write(char **ptr, ssize_t *err)
{
	int	total_write;

	total_write = 0;
	while (**ptr != '%' && **ptr != '\0')
	{
		if (write(1, *ptr, 1) != 1)
		{
			*err = 1;
			return (total_write);
		}
		*ptr = *ptr + 1;
		total_write += 1;
	}
	return (total_write);
}

int	check_and_write(char **ptr, va_list ap, ssize_t *err)
{
	int		total_write;
	char	*start;

	start = *ptr;
	total_write = 0;
	while (!is_term(**ptr) && **ptr != '\0')
		*ptr = *ptr + 1;
	if (**ptr != '\0')
	{
		total_write += gestor_args(&start, **ptr, ap, err);
		*ptr = *ptr + 1;
	}
	return (total_write);
}
