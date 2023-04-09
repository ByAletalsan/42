/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 14:59:09 by atalaver          #+#    #+#             */
/*   Updated: 2023/04/09 16:14:45 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_inv_arg(char *s)
{
	printf("%s <number_of_philosophers> <time_to_die> ", s);
	printf("<time_to_eat> <time_to_eat> ");
	printf("[number_of_times_each_philosopher_must_eat]\n");
	exit(1);
}

static void	ft_free(t_philo *philos, pthread_mutex_t *mutex,
						t_dato datos)
{
	int	i;

	free(philos);
	i = 0;
	while (i < datos.n_philos + 1)
	{
		pthread_mutex_destroy(&mutex[i]);
		i++;
	}
	free(mutex);
}

int	main(int argc, char **argv)
{
	t_philo			*philos;
	t_dato			datos;
	int				error;
	pthread_mutex_t	*mutex;

	if (argc != 5 && argc != 6)
		ft_inv_arg(argv[0]);
	ft_load_datos(&datos, argc, argv);
	mutex = ft_init_mutex(datos);
	if (!mutex)
		return (printf("Error::Create mutex\n"), 1);
	philos = ft_create_philos(datos, mutex);
	if (!philos)
		return (printf("Error::Malloc philos\n"), 1);
	error = ft_create_threads(philos);
	if (error)
		return (1);
	//error = ft_join_threads(philos);
	//if (error)
	//	return (ft_free(philos, mutex, datos), 1);
	ft_checking_philos(philos, datos);
	ft_free(philos, mutex, datos);
	return (0);
}
