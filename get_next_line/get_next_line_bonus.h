/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 09:10:53 by atalaver          #+#    #+#             */
/*   Updated: 2022/10/20 20:16:54 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <stdlib.h>
# include <unistd.h>

//Parte principal
char	*get_next_line(int fd);
//Funciones adicionales
void	*ft_calloc(int nmemb, int size);
int		ft_strlen(char *str);
char	*ft_strjoin(char *s1, char *s2);
int		ft_chr_exist(char *s, int c);

#endif