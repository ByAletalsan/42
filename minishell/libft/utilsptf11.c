/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsptf11.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvasco-m <dvasco-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 14:02:07 by dvasco-m          #+#    #+#             */
/*   Updated: 2023/01/26 20:31:20 by dvasco-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	write_char_w(char c, t_parms *parms, ssize_t *err)
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
	i = 0;
	fill_zeros_spaces_char(parms, block, &i);
	block[i] = '\0';
	total_write = write(1, block, ft_strlen_ptf(block));
	if (total_write != (int)ft_strlen_ptf(block))
		*err = 1;
	free(block);
	if (write(1, &c, 1) != 1)
	{
		*err = 1;
		return (total_write);
	}
	return (total_write + 1);
}

int	gst_and_wr_chr(t_parms *parms, va_list ap, ssize_t *err, char term)
{
	int		total_write;
	char	c;

	total_write = 0;
	if (term == '%')
		c = '%';
	else
		c = c_var(ap);
	if (parms->width)
	{
		if (parms->minus)
			total_write = write_char_minus_w(c, parms, err);
		else
			total_write = write_char_w(c, parms, err);
	}
	else
	{
		total_write = write(1, &c, 1);
		if (total_write != 1)
			*err = 1;
	}
	return (total_write);
}

int	write_str(char *str, ssize_t *err)
{
	int		total_write;
	size_t	len_str;

	total_write = 0;
	len_str = 0;
	if (str == NULL)
	{
		total_write = write(1, "(null)", 6);
		if (total_write != 6)
			*err = 1;
		return (total_write);
	}
	len_str = ft_strlen_ptf(str);
	total_write = write(1, str, len_str);
	if (total_write != (int)(len_str))
		*err = 1;
	return (total_write);
}

int	write_block_w_m(char *block, t_parms *parms, ssize_t *err)
{
	int		total_write;
	int		i;
	size_t	len_block;

	len_block = ft_strlen_ptf(block);
	total_write = 0;
	i = 0;
	if (parms->width > len_block)
	{
		total_write = write(1, block, len_block);
		if (total_write != (int)(len_block))
			*err = 1;
		else
		{
			while ((i < (int)(parms->width - len_block)) && *err == 0)
			{
				if (write(1, " ", 1) != 1)
					*err = 1;
				i++;
			}
		}
	}
	else
		total_write = write_str(block, err);
	return (total_write + i);
}

int	write_block_w_0(char *block, t_parms *parms, ssize_t *err)
{
	int		total_write;
	int		i;
	size_t	len_block;

	len_block = ft_strlen_ptf(block);
	total_write = 0;
	i = 0;
	if (parms->width > len_block)
	{
		while ((i < (int)(parms->width - len_block)) && *err == 0)
		{
			if (write(1, "0", 1) != 1)
				*err = 1;
			i++;
		}
		total_write = write(1, block, len_block);
		if (total_write != (int)len_block)
			*err = 1;
	}
	else
		total_write = write_str(block, err);
	return (total_write + i);
}
