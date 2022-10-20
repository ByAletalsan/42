/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 09:10:53 by atalaver          #+#    #+#             */
/*   Updated: 2022/10/20 20:05:08 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>

//Parte principal
char	*get_next_line(int fd);
char	*ft_read_buffer_to_n(int fd, char *str);
char	*ft_read_line(char *str);
char	*ft_remove_line(char *str);
char	*ft_add_and_free(char *str, char *buff);
//Funciones adicionales
void	*ft_calloc(int nmemb, int size);
void	ft_bzero(void *s, int n);
int		ft_strlen(char *str);
char	*ft_strjoin(char *s1, char *s2);
int		ft_chr_exist(char *s, int c);

#endif