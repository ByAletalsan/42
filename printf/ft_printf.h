/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 20:21:55 by atalaver          #+#    #+#             */
/*   Updated: 2022/10/12 21:28:02 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <unistd.h>
# include "libft/libft.h"

typedef struct s_bonus
{
	int				menos;
	int				cero;
	int				punto;
	int				width;
	int				almoadilla;
	int				espacio;
	int				mas;
	int				limit;
}					t_bonus;

int		ft_printf(char const *s, ...);
int		ft_print_char(char c);
int		ft_print_char_bonus(t_bonus *b, char c);
int		ft_print_string(char *s, t_bonus *b);
int		ft_print_int(int n, t_bonus *b);
int		ft_print_memory(unsigned long long n, t_bonus *b);
int		ft_print_uint(unsigned int n, t_bonus *b);
int		ft_print_hexa(unsigned int n, char format);
void	ft_startbonus(t_bonus *b);
void	ft_add_bonus(t_bonus *b, const char *s, int *i);
int		ft_print_spaces(t_bonus *b, unsigned long long n, int p);
int		ft_print_ceros(t_bonus *b);
int		ft_print_spaces_int(t_bonus *b, int p);

void	ft_print_bonus(t_bonus *b);

#endif