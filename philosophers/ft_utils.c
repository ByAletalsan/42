/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 16:24:36 by atalaver          #+#    #+#             */
/*   Updated: 2023/02/05 17:02:46 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*ft_create_philos(t_dato datos, int *tenedores)
{
	t_philo	*philos;
	int		n_philos;
	int		i;

	philos = (t_philo *)ft_calloc(datos.n_philos + 1, sizeof(t_philo));
	if (!philos)
		return (NULL);
	i = 0;
	while (i < datos.n_philos)
	{
		philos[i].n_philo = i + 1;
		philos[i].datos = datos;
		philos[i].tenedor_rigth = &tenedores[i];
		if (i == 0)
			philos[i].tenedor_left = &tenedores[datos.n_philos - 1];
		else
			philos[i].tenedor_left = &tenedores[i - 1];
		i++;
	}
	return (philos);
}

void	ft_print_philo(t_philo p)
{
	printf("Philo No:%i\n", p.n_philo);
	printf("Tenedor left:%x\n", p.tenedor_left);
	printf("Tenedor rigth:%x\n\n", p.tenedor_rigth);
}

void	ft_load_datos(t_dato *datos, int argc, char **argv)
{
	datos->n_philos = ft_atoi(argv[1]);
	datos->time_to_die = ft_atoi(argv[2]);
	datos->time_to_eat = ft_atoi(argv[3]);
	datos->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		datos->times = ft_atoi(argv[5]);
	else
		datos->times = 0;
}
