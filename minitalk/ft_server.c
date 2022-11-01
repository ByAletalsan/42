/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_server.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 08:36:24 by atalaver          #+#    #+#             */
/*   Updated: 2022/11/01 19:32:53 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_server.h"

//Variable global par almacenar los datos que no se pueden en la funcion
//No hace falta esta variable global si se ponen las variables como static
t_data	datos;

//Vamos insertando de bit en bit en el caracter hasta obtener los 8
//Solo insertamos los 1, los 0 simplemente seguimos deplazando al siguiente bit
void	ft_get_char(int n, siginfo_t *info, void *context)
{
	(void) context;
	if (n == SIGUSR2)
		datos.c |= 1 << datos.bit;
	datos.bit++;
	if (datos.bit == 8)
	{
		ft_printf("%c", datos.c);
		datos.c = 0;
		datos.bit = 0;
	}
	kill(info->si_pid, SIGUSR1);
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
	struct sigaction	sa;

	datos.bit = 0;
	datos.c = 0;
	ft_printf("%d\n", getpid());
	sa.sa_handler = SIG_DFL;
	sa.sa_sigaction = ft_get_char;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	signal(SIGINT, ft_exit);
	signal(SIGTERM, ft_exit);
	while (1)
		pause();
	return (0);
}
