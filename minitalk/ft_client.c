/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_client.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 09:04:06 by atalaver          #+#    #+#             */
/*   Updated: 2022/10/31 13:22:14 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_client.h"

/*
Vamos repasando bit a bit si es 1 o 0. 0 -> SIGUSR1 ; 1 -> SIGUSR2;
Y hacemos un delay de 200ms;
Ej de desplazamiento: 1 << 0 = 0001; 1 << 1 = 0010; 1 << 2 = 0100;
Ej de operacion: 1001 & 0001 = 0001 = 1; 1001 & 0010 = 0000 = 0;
De esta forma nos centramos solo en el bit deseado
*/
void	ft_send_char(char c, pid_t pid)
{
	int	bit;

	bit = 0;
	while (bit < 8)
	{
		if (c & (1 << bit))
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		usleep(200);
		bit++;
	}
}

//Recorremos el string enviando caracter a caracter
void	ft_send_string(char *s, pid_t pid)
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
int	ft_check_arg(int argc, char **argv)
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

int	main(int argc, char **argv)
{
	pid_t	pid;

	if (!ft_check_arg(argc, argv))
	{
		ft_printf("Error con los argumentos");
		return (1);
	}
	pid = ft_atoi(argv[1]);
	ft_send_string(argv[2], pid);
	return (0);
}
