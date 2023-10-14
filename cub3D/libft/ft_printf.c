/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvasco-m <dvasco-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 14:07:05 by dvasco-m          #+#    #+#             */
/*   Updated: 2023/01/26 20:30:22 by dvasco-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf(const	char	*s, ...)
{
	va_list	ap;
	int		total_write;
	char	*ptr;
	ssize_t	err;

	va_start(ap, s);
	err = 0;
	ptr = (char *)s;
	total_write = 0;
	if (ptr != NULL)
	{
		while (*ptr != '\0' && !err)
		{
			total_write += walk_and_write(&ptr, &err);
			if (*ptr == '%' && !err)
			{
				ptr++;
				total_write += check_and_write(&ptr, ap, &err);
			}
		}
	}
	va_end(ap);
	if (err)
		return (-1);
	return (total_write);
}
