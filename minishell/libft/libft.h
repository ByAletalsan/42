/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 20:19:44 by dvasco-m          #+#    #+#             */
/*   Updated: 2023/06/24 22:14:32 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <sys/types.h>
# include <sys/stat.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <string.h>
# include <errno.h>
# include <sys/errno.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

typedef struct v_parms
{
	size_t	zero;
	size_t	plus;
	size_t	space;
	size_t	minus;
	size_t	point;
	size_t	hash;
	size_t	width;
	size_t	prec;
	size_t	only_width;
	size_t	total_write;
	size_t	hex0;
	char	ox[3];
	size_t	num0;

}	t_parms;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct counters
{
	int	i;
	int	j;
	int	k;
	int	size;
}				t_cnt;

typedef struct simulation
{
	int	sa;
	int	sb;
	int	ss;
	int	pa;
	int	pb;
	int	ra;
	int	rb;
	int	rr;
	int	rra;
	int	rrb;
	int	rrr;
	int	total;
}				t_simulation;

typedef struct stack_list
{
	int					number;
	int					pos;
	struct stack_list	*next;
	t_simulation		moves;
}				t_stl;

typedef struct stack
{
	t_stl	*stack;
	char	ab;
	int		size;
	int		min;
	int		max;
}				t_stack;

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void	*));
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstlast(t_list *lst);
int		ft_lstsize(t_list *lst);
void	ft_lstadd_front(t_list **lst, t_list *new);
t_list	*ft_lstnew(void *content);
void	free_content_lst(void *content);
t_list	*matrix_to_list(void **matrix);
void	print_list(t_list	*lista);
int		quotes(char c, int *q);
int		ft_len_matrix2(char **matrix2);
int		ft_is_full_digit(char *str);
void	ft_order_list(t_list *list);
int		ft_len_list(t_list *list);

void	ft_putnbr_fd(int n, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	*ft_itoa(int n);
char	**ft_split(char const *s, char c);
char	**ft_split_m(char *s, char c);
char	**ft_split_m2(char *s, char c);
char	*ft_strtrim(char const *s1, char const *set);
/**
 * @brief "Reserva con malloc y devuelve una nueva
 * string, formada por la concatenación de s1 y s2"
 * 
 * @param s1 
 * @param s2 
 * @return char* 
 */
char	*ft_strjoin(char const *s1, char const *s2);
/**
 * @brief "Reserva (con malloc(3)) y devuelve una substring 
 * de la string 's'. La substring epieza desde el índice
 * 'start' y tiene una longitud máxima 'len'."
 * 
 * @param s 
 * @param start 
 * @param len 
 * @return char* 
 */
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(const char *s1);
void	*ft_calloc(size_t count, size_t size);
int		ft_atoi(const char *str);
int		ft_toupper(int c);
int		ft_tolower(int c);
char	*ft_strrchr(const char *s, int c);
/**
 * @brief "locate a substring in a string"
 * 
 * @param haystack 
 * @param needle 
 * @param len 
 * @return char* 
 */
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strcmp(const char *s1, const char *s2);
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
char	*ft_strchr(const char *s, int c);
void	*ft_memset(void *s, int c, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_isprint(int c);
int		ft_isdigit(int c);
int		ft_isascii(int c);
int		ft_isalpha(int c);
int		ft_isalnum(int c);
int		ft_isspace(char c);
int		ft_min(int a, int b);
char	*ft_strcpy_range(char *str, int i, int j);
void	ft_bzero(void *s, size_t n);

char	*read_fd(int fd, char *buff, size_t *eof, ssize_t bytes_read);
char	*save_line(char *line, char *buff, size_t i);
char	*make_line(char *line, char *buff, size_t size, size_t eof);
char	*build_line(char *buff, char *line, ssize_t *line_complete, size_t eof);
char	*get_next_line(int fd);

void	init_parms(t_parms	*parms);
size_t	ft_strlen_ptf(const char *s);
int		ptf_count_figures(int n);
void	fill_dc_base_ptf(char *dec_base);
void	bld_nmb_ptf(char *number, int n, int figures, int sign);
char	*ft_itoa_ptf(int n);
int		ptf_count_figures_u(unsigned int n);
void	bld_nmb_ptf_u(char *number, unsigned int n, int figures);
char	*ft_uitoa(unsigned int n);
int		ptf_count_figures_hex(unsigned int n);
void	fill_hex_base(char *hex_base, char c);
void	bld_nmb_ptf_hex(char *number, unsigned int n, int figures, char c);
char	*ft_itoa_ptf_hex(unsigned int n, char c);
int		ptf_count_figures_ptr(unsigned long int n);
void	fill_ptr_base(char *hex_base);
void	bld_nmb_ptf_ptr(char *number, unsigned long int n, int figures);
char	*ft_itoa_ptf_ptr(unsigned long int n);
char	*i_d_var(va_list ap, t_parms *parms);
char	*u_var(va_list ap, t_parms *parms);
char	c_var(va_list ap);
char	*s_var(va_list ap);
char	*p_var(va_list ap, t_parms *parms);
char	*x_var(va_list ap, char v_type, t_parms *parms);
size_t	set_width(char **start, size_t i);
size_t	set_prec(char **start, size_t i, t_parms *parms);
size_t	is_term(char c);
size_t	is_flag(char c);
void	analize_flags(t_parms *parms, char **start);
void	pos_plus_space(size_t *j, char *number, char *block, t_parms *parms);
void	pos_plus_minus(size_t *j, char *number, char *block, t_parms *parms);
size_t	set_nmb_block(char *number, char *block, size_t pos, t_parms *parms);
size_t	eval_flags_space_plus(t_parms *parms, char *n, size_t *j, char *block);
char	*fill_w_zero_int(t_parms *parms, char *number, ssize_t *err);
char	*fill_minus_int(t_parms *parms, char *number, ssize_t *err);
char	*fill_space_int(t_parms *parms, char *number, ssize_t *err);
char	*fill_without_width_int(t_parms *parms, char *number, ssize_t *err);
int		write_int(t_parms *parms, char *number, ssize_t *err);
void	fill_block_prec_zeros(size_t zeros, char *block, size_t *i);
void	fill_block_prc_nmb(char *number, char *block, size_t *i, size_t digits);
void	mke_special_zero(t_parms *parms, char *block);
void	mke_prc_blk(t_parms *parms, char *number, size_t digits, char *block);
char	*create_special_zero_block(t_parms *parms);
char	*fill_prec_int(t_parms *parms, char *number, ssize_t *err);
char	*fill_prc_wd_l(char *block, char *aux, t_parms *parms, size_t szblck);
char	*fill_prc_wd_r(char *block, char *aux, t_parms *parms);
char	*fill_prc_wd(char *block, t_parms *parms, ssize_t *err, size_t szblck);
int		write_int_prec(t_parms *parms, char *number, ssize_t *err);
int		gst_and_write_int(t_parms *parms, va_list ap, ssize_t *err, ssize_t tp);
int		write_char_minus_w(char c, t_parms *parms, ssize_t *err);
void	fill_zeros_spaces_char(t_parms *parms, char *block, size_t *i);
int		write_char_w(char c, t_parms *parms, ssize_t *err);
int		gst_and_wr_chr(t_parms *parms, va_list ap, ssize_t *err, char term);
int		write_str(char *str, ssize_t *err);
int		write_block_w_m(char *block, t_parms *parms, ssize_t *err);
int		write_block_w_0(char *block, t_parms *parms, ssize_t *err);
int		write_block_w(char *block, t_parms *parms, ssize_t *err);
int		write_str_w(char *block, t_parms *parms, ssize_t *err);
char	*block_str_prec(char *str, t_parms *parms, ssize_t *err);
int		gestor_and_write_str(t_parms *parms, va_list ap, ssize_t *err);
int		write_ox_block(t_parms *parms, char *block, ssize_t *err);
int		write_ox_block_spaces(t_parms *parms, char *block, ssize_t *err);
void	print_c_zero_space(char c, int *total_write, ssize_t *err);
int		write_spaces_zeros_ox_block(t_parms *parms, char *block, ssize_t *err);
char	*new_block_prec(t_parms *parms, char *block, ssize_t *err);
char	*new_block_prec_special_0(ssize_t *err);
int		write_ptr_prec(t_parms *parms, char *block, ssize_t *err);
int		write_ptr_noprec(t_parms *parms, char *block, ssize_t *err);
int		gst_and_wr_pnt(t_parms *parms, va_list ap, ssize_t *err);
int		wrhex_ox_block(t_parms *parms, char *block, ssize_t *err);
ssize_t	print_ox_hex(t_parms *parms, size_t *k);
int		wrhex_ox_block_spaces(t_parms *parms, char *block, ssize_t *err);
int		print_zero_space(t_parms *parms, char c, size_t hollow, ssize_t *err);
ssize_t	print_ox(t_parms *parms, size_t *k);
int		wrhex_spaces_zeros_ox_block(t_parms *parms, char *block, ssize_t *err);
char	*new_block_hx_prec(t_parms *parms, char *block, ssize_t *err);
char	*new_block_hx_prec_special_0(ssize_t *err, t_parms *parms);
int		write_hex_prec(t_parms *parms, char *block, ssize_t *err, char term);
int		write_hex_noprec(t_parms *parms, char *block, ssize_t *err, char term);
int		gst_and_wr_hex(t_parms *parms, va_list ap, ssize_t *err, char term);
int		gestor_args(char **start, char term, va_list ap, ssize_t *err);
int		wrhex_pr_spcs_zeros_ox_block(t_parms *parms, char *block, ssize_t *err);
int		walk_and_write(char **ptr, ssize_t *err);
int		check_and_write(char **ptr, va_list ap, ssize_t *err);
int		ft_printf(const	char	*s, ...);

t_stl	*ft_new_node(int number);
void	ft_add_node_front(t_stl **lst, t_stl *new);
int		ft_stacksize(t_stl *lst);
t_stl	*ft_stacklast(t_stl *lst);
t_stl	*ft_stack2last(t_stl *lst);
void	ft_add_node_back(t_stl **lst, t_stl *new);
void	ft_del_node_back(t_stl **lst);
void	ft_del_node_front(t_stl **lst);
void	ft_free_stack(t_stl **lst);
t_stl	*find_node(t_stl *stack, int i);

void	swap(t_stl **stack, char ab);
void	sswap(t_stl **stack_a, t_stl **stack_b, char simu);
void	push(t_stl **stack_o, t_stl **stack_d, char ab_d);
void	push_n(t_stl **lstack_o, t_stl **lstack_d, int n, char ab_d);
void	rotate(t_stl **stack, char ab);
void	rotate_n(t_stl **stack, int n, char ab);
void	rrotate(t_stl **stack_a, t_stl **stack_b, char simu);
void	rrotate_n(t_stl **stack_a, t_stl **stack_b, char simu, int n);
void	reverse_rotate(t_stl **stack, char ab);
void	reverse_rotate_n(t_stl **stack, int n, char ab);
void	rreverse_rotate(t_stl **stack_a, t_stl **stack_b, char simu);
void	rreverse_rotate_n(t_stl **stack_a, t_stl **stack_b, char simu, int n);

void	cre_lstks(t_stack *lstack_a, t_stack *lstack_b, t_stl *stack);
t_stl	*push_swap(t_stl *stack);
t_stl	*create_stack_a(char **argv, int *valid, t_stl *stack_a);
void	index_position(t_stl *stack_a);
void	ft_ord3(t_stack *lstack_a);
void	ft_ord2(t_stack *lstack_a);
void	initial_moves(t_stack *lstack_a, t_stack *lstack_b);
void	init_simulation(t_stl *stack_b);
void	w_uu(t_stack *s_a, t_stack *s_b, int pos, t_simulation *uu);
void	w_ud(t_stack *s_a, t_stack *s_b, int pos, t_simulation *ud);
void	w_du(t_stack *s_a, t_stack *s_b, int pos, t_simulation *du);
void	w_dd(t_stack *s_a, t_stack *s_b, int pos, t_simulation *dd);
void	save_moves(t_simulation *xx, t_stack *lstack_b, int pos);
void	calc_rb(t_stl *node, int size, int pos, t_simulation *xx);
void	calc_rrb(t_stl *node, int size, int pos, t_simulation *xx);
void	calc_ramin(t_stl *node, int min, t_simulation *xx);
void	calc_rramin(t_stl *node, int min, int size, t_simulation *xx);
void	calc_ramax(t_stl *node, int max, t_simulation *xx);
void	calc_rramax(t_stl *node, int max, int size, t_simulation *xx);
void	calc_ragen(t_stl *node, int size, int pos, t_simulation *xx);
int		calc_offset_rragen(t_stl *node, int size, int pos);
void	calc_rragen(t_stl *node, int size, int pos, t_simulation *xx);
void	calc_maxmin(t_stack *lstack_a);
void	optimize_rr(t_simulation *xx);
void	optimize_rrr(t_simulation *xx);
void	calc_moves(t_stack *lstack_a, t_stack *lstack_b, int pos);
int		make_simulation(t_stack	*lstack_a, t_stack *lstack_b);
void	make_best_move(t_stack *s_a, t_stack *s_b, int selected);
void	actualize_stacks(t_stack *lstack_a, t_stack *lstack_b);
void	final_order(t_stack *s_a);
void	print_index(t_stl *stack);
int		is_sort(t_stl *stack_a);
void	ft_free_params(char **array_ptr);
int		size_args(char **argv, int argc);
char	*create_array_params(char **argv, int argc, int *lzeros);
char	**create_params(char **argv, int argc, char *array_params);
int		valid_param(char *param);
int		check_repeated(t_stl *stack_a);
int		cmp_extremes(int sign, char *number, char *maxint, char *minint);
int		valid_number(char *number);
int		duplicated_number(t_stl *stack_a);
void	write_error(void);
void	write_error_free_params(char ***params);
void	write_error_free_params_stacka(char ***params, t_stl **stack_a);
void	free_params_stacka(char ***params, t_stl **stack_a);
int		calc_extra_zeros(char *number, t_cnt *ijk);
char	*save_each_number(t_cnt *ijk, char *a_params, char **argv, int *lzeros);
int		evaluate_min(char *number, char *minint, int size, int i);
int		evaluate_max(char *number, char *maxint, int size, int i);
void	reset_moves(t_simulation *xx);
void	ft_leaks(void);
void	print_stacka(t_stl *stack_a);

int		slct_mve(char *move, t_stack *lstack_a, t_stack *lstack_b, size_t size);
t_stl	*exec_moves(t_stl *stack, int *valid, char *array_moves);
char	*read_moves(char *array_moves);
void	free_exec_moves(char **movements, t_stl **stack_b);
void	ft_leaks2(void);

#endif
