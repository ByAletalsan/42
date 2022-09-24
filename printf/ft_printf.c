/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 20:14:11 by atalaver          #+#    #+#             */
/*   Updated: 2022/09/24 21:56:04 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"
#include "libft/libft.h"

static void	ft_print_special(char const c, va_list *arg)
{
	if (c == '%')
		ft_putchar_fd((int) '%', 1);
	if (c == 'c')
		ft_putchar_fd(va_arg(*arg, int), 1);
	if (c == 's')
		ft_putstr_fd(va_arg(*arg, char *), 1);
	if (c == 'i')
		ft_putnbr_fd(va_arg(*arg, int), 1);
}

int	ft_printf(char const *s, ...)
{
	va_list	arg;
	int		i;

	i = 0;
	va_start(arg, s);
	while (s[i] != '\0')
	{
		if (s[i] == '%')
			ft_print_special(s[++i], &arg);
		else
			write(1, &s[i], 1);
		i++;
	}
	return (0);
}
