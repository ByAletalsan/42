/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_client.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 09:04:06 by atalaver          #+#    #+#             */
/*   Updated: 2023/01/30 09:35:40 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_make.h"

//Para checkear si hemos recibido la señal
int	g_check;

/*
Vamos repasando bit a bit si es 1 o 0. 0 -> SIGUSR1 ; 1 -> SIGUSR2;
Y hacemos un delay de 200ms;
Ej de desplazamiento: 1 << 0 = 0001; 1 << 1 = 0010; 1 << 2 = 0100;
Ej de operacion: 1001 & 0001 = 0001 = 1; 1001 & 0010 = 0000 = 0;
De esta forma nos centramos solo en el bit deseado
*/
static void	ft_send_char(char c, pid_t pid)
{
	int	bit;

	bit = 0;
	while (bit < 8)
	{
		if (c & (1 << bit))
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		while (!g_check)
			usleep(1);
		g_check = 0;
		bit++;
	}
}

//Recorremos el string enviando caracter a caracter
static void	ft_send_string(char *s, pid_t pid)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		ft_send_char(s[i], pid);
		i++;
	}
}

//Chequemos que los argumentos esten bien
static int	ft_check_arg(int argc, char **argv)
{
	int	i;

	i = 0;
	if (argc != 3)
		return (0);
	while (argv[1][i] != '\0')
	{
		if (!ft_isdigit(argv[1][i]))
			return (0);
		i++;
	}
	return (1);
}

static void	ft_handler(int n)
{
	(void)n;
	g_check = 1;
}

int	main(int argc, char **argv)
{
	pid_t	pid;

	g_check = 0;
	signal(SIGUSR1, ft_handler);
	signal(SIGUSR1, ft_handler);
	if (!ft_check_arg(argc, argv))
	{
		ft_printf("Error con los argumentos");
		return (1);
	}
	pid = ft_atoi(argv[1]);
	ft_send_string(argv[2], pid);
	return (0);
}
