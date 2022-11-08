/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push_swap.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 08:32:22 by atalaver          #+#    #+#             */
/*   Updated: 2022/11/08 12:55:19 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PUSH_SWAP_H
# define FT_PUSH_SWAP_H
# include <stdlib.h>
# include <limits.h>

typedef struct pila
{
	char	c;
	int		*p;
	int		len;
}	t_pila;

void	ft_logic(t_pila *a, t_pila *b);
void	ft_order_two(t_pila *a);
void	ft_order_three(t_pila *a);
void	ft_order_four(t_pila *a, t_pila *b);
void	ft_order_five(t_pila *a, t_pila *b);
int		ft_find_low(t_pila *a);
int		ft_n_rotate(t_pila *a, int n);
int		ft_n_rev_rotate(t_pila *a, int n);
void	ft_order_end(t_pila *a);
int		ft_find_low_of_top(t_pila *a, int n);
int		ft_return_find_low_of_top(t_pila *a, int n, int i);
int		ft_find_indice(t_pila *a, int n);
//Check and utils
int		ft_check_digit(int argc, char **argv);
int		ft_check_limit(int argc, char **argv);
int		ft_check_rep(t_pila *a);
t_pila	*ft_fill(int len, char **argv, char c);
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
char	**ft_split(char const *s, char c);

#endif