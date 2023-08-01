/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsptf5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvasco-m <dvasco-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 13:48:18 by dvasco-m          #+#    #+#             */
/*   Updated: 2023/01/26 20:30:56 by dvasco-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*s_var(va_list ap)
{
	char	*str;

	str = va_arg(ap, char *);
	return (str);
}

char	*p_var(va_list ap, t_parms *parms)
{
	char				*str;
	unsigned long int	dir_p;

	str = NULL;
	dir_p = va_arg(ap, unsigned long int);
	if (dir_p == 0)
		parms->hex0 = 1;
	str = ft_itoa_ptf_ptr(dir_p);
	return (str);
}

char	*x_var(va_list ap, char v_type, t_parms *parms)
{
	char				*str;
	unsigned int		x;

	str = NULL;
	x = va_arg(ap, unsigned int);
	if (x == 0)
		parms->hex0 = 1;
	if (v_type == 'X')
		str = ft_itoa_ptf_hex(x, 'A');
	else
		str = ft_itoa_ptf_hex(x, 'a');
	return (str);
}

size_t	set_width(char **start, size_t i)
{
	size_t	j;
	size_t	result;
	char	*s;

	j = i;
	s = *start;
	while ((**start >= '0' && **start <= '9') && **start != '\0')
	{
		*start = *start + 1;
		i++;
	}
	result = 0;
	while ((s[j] >= '0' && s[j] <= '9') && j < i)
	{
		result = (s[j] - 48) + (result * 10);
		j++;
	}
	return (result);
}

size_t	set_prec(char **start, size_t i, t_parms *parms)
{
	size_t	j;
	size_t	result;
	char	*s;

	while (**start == '.')
	{
		parms->point += 1;
		*start = *start + 1;
	}
	j = i;
	s = *start;
	result = 0;
	if (parms->point)
	{
		while ((**start >= '0' && **start <= '9') && **start != '\0')
		{
			*start = *start + 1;
			i++;
		}
		while ((s[j] >= '0' && s[j] <= '9') && j < i)
			result = (s[j++] - 48) + (result * 10);
	}
	return (result);
}
