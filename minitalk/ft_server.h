/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_server.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 08:48:32 by atalaver          #+#    #+#             */
/*   Updated: 2022/10/31 12:53:25 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SERVER_H
# define FT_SERVER_H
# include <sys/types.h>
# include <unistd.h>
# include <signal.h>
# include <stdlib.h>

//Estructura para guardar los datos que no se pueden guardar en la funcion
//de la señal. Y como son 2 datos y solo se puede 1 variable gloabl pues hacemos
//un struct con los dos
typedef struct data
{
	char	c;
	int		bit;
}	t_data;

int		ft_printf(char const *s, ...);

#endif