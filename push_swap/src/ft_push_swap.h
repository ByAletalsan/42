/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push_swap.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 08:32:22 by atalaver          #+#    #+#             */
/*   Updated: 2023/01/30 15:53:07 by atalaver         ###   ########.fr       */
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

typedef struct cost
{
	int	ra;
	int	rb;
	int	rr;
	int	rra;
	int	rrb;
	int	rrr;
	int	total;
}	t_cost;

void	ft_logic(t_pila *a, t_pila *b);
void	ft_order_two(t_pila *a);
void	ft_order_three(t_pila *a);
void	ft_order_four(t_pila *a, t_pila *b);
void	ft_order_five(t_pila *a, t_pila *b);
void	ft_order(t_pila *a, t_pila *b);
int		ft_order_start(t_pila *a);
int		ft_find_low(t_pila *a);
void	ft_push_start(t_pila *a, t_pila *b);
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
void	ft_free_split(char **s);
t_pila	*ft_fill(int len, char **argv, char c);
long	ft_atol(char *str);
t_cost	*ft_ini_cost(void);
void	ft_cost(t_pila *a, t_pila *b, int i, t_cost *p);
//Movements
void	ft_rotate(t_pila *p);
void	ft_rev_rotate(t_pila *p);
void	ft_swap(t_pila *p);
void	ft_push(t_pila *dest, t_pila *ori);
void	ft_rotate_both(t_pila *a, t_pila *b);
void	ft_rev_rotate_both(t_pila *a, t_pila *b);
//Libft
int		ft_printf(char const *s, ...);
void	*ft_calloc(size_t nmemb, size_t size);
int		ft_atoi(const char *str);
int		ft_isdigit(int c);
char	**ft_split(char const *s, char c);

#endif