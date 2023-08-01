/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsptf6.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvasco-m <dvasco-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 13:54:42 by dvasco-m          #+#    #+#             */
/*   Updated: 2023/01/26 20:31:01 by dvasco-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	is_term(char c)
{
	if (c == 'i' || c == 'd' || c == 's' || c == 'c'
		|| c == 'x' || c == 'p' || c == 'X' || c == '%' || c == 'u')
		return (1);
	return (0);
}

size_t	is_flag(char c)
{
	if (c == '-' || c == '+' || c == ' ' || c == '#' || c == '0')
		return (1);
	return (0);
}

void	analize_flags(t_parms *parms, char **start)
{
	while (is_flag(**start))
	{
		if (**start == '-')
			parms->minus += 1;
		if (**start == '+')
			parms->plus += 1;
		if (**start == ' ')
			parms->space += 1;
		if (**start == '#')
			parms->hash += 1;
		if (**start == '0')
			parms->zero += 1;
	*start = *start + 1;
	}
}

void	pos_plus_space(size_t *j, char *number, char *block, t_parms *parms)
{
	if (number[0] != '-' && parms->minus)
	{
		if (parms->plus)
			block[*j] = '+';
		if (!parms->plus && parms->space)
			block[*j] = ' ';
		if (parms->plus || (!parms->plus && parms->space))
			*j = *j + 1;
	}
	if (number[0] != '-' && parms->plus && !parms->minus && !parms->space)
	{
		if (!parms->zero)
		{
			block[*j] = '+';
			*j = *j + 1;
		}
	}
	if (number[0] != '-' && !parms->plus && !parms->minus && parms->space)
	{
		if (!parms->zero)
		{
			block[*j] = ' ';
			*j = *j + 1;
		}
	}
}

void	pos_plus_minus(size_t *j, char *number, char *block, t_parms *parms)
{
	if (number[0] != '-' && parms->plus)
	{
		block[*j] = '+';
		*j = *j + 1;
	}
	if (number[0] != '-' && !parms->plus && parms->space)
	{
		block[*j] = ' ';
		*j = *j + 1;
	}
}
