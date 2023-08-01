/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvasco-m <dvasco-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 20:19:44 by dvasco-m          #+#    #+#             */
/*   Updated: 2022/12/12 14:45:34 by dvasco-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <sys/types.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

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
char	*fill_prc_wd_r(char *block, char *aux, t_parms *parms, size_t szblck);

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

#endif