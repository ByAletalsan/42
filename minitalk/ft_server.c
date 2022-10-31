/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_server.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 08:36:24 by atalaver          #+#    #+#             */
/*   Updated: 2022/10/31 13:08:11 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_server.h"

//Variable global par almacenar los datos que no se pueden en la funcion
//No hace falta esta variable global si se ponen las variables como static
t_data	datos;

//Vamos insertando de bit en bit en el caracter hasta obtener los 8
//Solo insertamos los 1, los 0 simplemente seguimos deplazando al siguiente bit
void	ft_get_char(int n)
{
	if (n == SIGUSR2)
		datos.c |= 1 << datos.bit;
	datos.bit++;
	if (datos.bit == 8)
	{
		ft_printf("%c", datos.c);
		datos.c = 0;
		datos.bit = 0;
	}
}

//El void es para que no nos de el error de no hacer nada con la n
void	ft_exit(int n)
{
	(void)n;
	exit(0);
}

/*
Ajustamos las señales para que hagan lo que queramos y hacemos un bucle que
espera hasta que llegue alguna señal
Puesto que es un bucle infinito vamos a gestionar las señales que utilizaremos
para detener el programa de forma correcta.
*/
int	main(void)
{
	datos.bit = 0;
	datos.c = 0;
	ft_printf("%d\n", getpid());
	signal(SIGUSR1, ft_get_char);
	signal(SIGUSR2, ft_get_char);
	signal(SIGINT, ft_exit);
	signal(SIGTERM, ft_exit);
	while (1)
		pause();
	return (0);
}
