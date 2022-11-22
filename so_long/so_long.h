/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 10:27:08 by atalaver          #+#    #+#             */
/*   Updated: 2022/11/22 12:21:17 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include "mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>

//Map
char	*ft_read_map(const char	*s);
int		ft_check_map(const char *s);
int		ft_check_ber(const char *s);
int		ft_check_limit(const char *s);
//Libft
size_t	ft_strlen(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_printf(char const *s, ...);
//GET_NEXT_LINE
char	*get_next_line(int fd);

#endif