/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 20:21:55 by atalaver          #+#    #+#             */
/*   Updated: 2022/10/08 12:09:52 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <unistd.h>
# include "libft/libft.h"

int	ft_printf(char const *s, ...);
int	ft_print_char(char c);
int	ft_print_string(char *s);
int	ft_print_int(int n);
int	ft_print_memory(unsigned long long n);
int	ft_print_uint(unsigned int n);
int	ft_print_hexa(unsigned int n, char format);

#endif