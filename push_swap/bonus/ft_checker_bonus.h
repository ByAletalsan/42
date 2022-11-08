/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checker_bonus.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 17:29:28 by atalaver          #+#    #+#             */
/*   Updated: 2022/11/08 19:27:27 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CHECKER_BONUS_H
# define FT_CHECKER_BONUS_H
# include <stdlib.h>
# include <limits.h>
# define STDERR 2

typedef struct pila
{
	char	c;
	int		*p;
	int		len;
}	t_pila;

//Logic
void	ft_logic_checker(t_pila *a, t_pila *b);
void	ft_check_order(t_pila *a, t_pila *b);
//Check and utils
int		ft_check_digit(int argc, char **argv);
int		ft_check_limit(int argc, char **argv);
int		ft_check_rep(t_pila *a);
t_pila	*ft_fill(int len, char **argv, char c);
long	ft_atol(char *str);
//Movements
void	ft_rotate_bonus(t_pila *p);
void	ft_rev_rotate_bonus(t_pila *p);
void	ft_swap_bonus(t_pila *p);
void	ft_push_bonus(t_pila *dest, t_pila *ori);
void	ft_rotate_both_bonus(t_pila *a, t_pila *b);
void	ft_rev_rotate_both_bonus(t_pila *a, t_pila *b);
//Libft
int		ft_printf(char const *s, ...);
void	ft_putstr_fd(char *s, int fd);
void	*ft_calloc(size_t nmemb, size_t size);
int		ft_atoi(const char *str);
int		ft_isdigit(int c);
char	**ft_split(char const *s, char c);
char	*get_next_line(int fd);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

#endif
