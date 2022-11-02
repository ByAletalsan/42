/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push_swap.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 08:32:22 by atalaver          #+#    #+#             */
/*   Updated: 2022/11/02 12:38:08 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PUSH_SWAP_H
# define FT_PUSH_SWAP_H
# include <stdlib.h>
# include <limits.h>

typedef struct pila
{
	int	*p;
	int	len;
}	t_pila;

void	ft_logic(t_pila *a, t_pila *b);
//Check and utils
int		ft_check_digit(int argc, char **argv);
int		ft_check_limit(int argc, char **argv);
int		ft_check_rep(t_pila *a);
t_pila	*ft_fill(int len, char **argv);
long	ft_atol(char *str);
//Movements
void	ft_rotate(t_pila *p);
void	ft_rev_rotate(t_pila *p);
void	ft_swap(t_pila *p);
void	ft_push(t_pila *dest, t_pila *ori);
//Libft
int		ft_printf(char const *s, ...);
void	*ft_calloc(size_t nmemb, size_t size);
int		ft_atoi(const char *str);
int		ft_isdigit(int c);

#endif