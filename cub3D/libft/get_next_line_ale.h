/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_ale.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvasco-m <dvasco-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 09:10:53 by atalaver          #+#    #+#             */
/*   Updated: 2023/09/21 15:07:26 by dvasco-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_ALE_H
# define GET_NEXT_LINE_ALE_H
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

//Parte principal
char	*get_next_line_ale(int fd);
//Funciones adicionales
void	*ft_calloc_ale(int nmemb, int size);
int		ft_strlen_ale(char *str);
char	*ft_strjoin_ale(char *s1, char *s2);
int		ft_chr_exist_ale(char *s, int c);

#endif