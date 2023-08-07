/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 14:59:09 by atalaver          #+#    #+#             */
/*   Updated: 2023/08/07 18:10:20 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_inv_arg(char *s)
{
	printf("%s <number_of_philosophers> <time_to_die> ", s);
	printf("<time_to_eat> <time_to_eat> ");
	printf("[number_of_times_each_philosopher_must_eat]\n");
}

pthread_mutex_t	*ft_init_mutex(t_dato datos)
{
	pthread_mutex_t	*mutex;
	int				i;

	mutex = ft_calloc(datos.n_philos + 1, sizeof(pthread_mutex_t));
	if (!mutex)
		return (NULL);
	i = 0;
	while (i < datos.n_philos + 1)
	{
		pthread_mutex_init(&mutex[i], NULL);
		i++;
	}
	return (mutex);
}

static int	ft_check_arg(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (ft_is_number(argv[i]))
			return (printf("ERROR::Arg invalid!\n"), 1);
		i++;
	}
	return (0);
}

static void	ft_free(t_philo *philos, t_dato *datos)
{
	int	i;

	i = 0;
	while (i < datos->n_philos)
	{
		pthread_mutex_destroy(&philos[i].mutex_time_lunch);
		pthread_mutex_destroy(&datos->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&datos->mutex_printf);
	pthread_mutex_destroy(&datos->mutex_end);
	free(datos->forks);
	free(philos);
}

int	main(int argc, char **argv)
{
	t_dato			datos;
	t_philo			*philos;

	if (argc != 5 && argc != 6)
		return (ft_inv_arg(argv[0]), 1);
	if (ft_check_arg(argc, argv))
		return (1);
	if (ft_load_datos(&datos, argc, argv))
		return (1);
	datos.forks = ft_init_mutex(datos);
	if (!datos.forks)
		return (printf("Error::Create mutex\n"), 1);
	philos = ft_create_philos(&datos);
	if (!philos)
		return (printf("Error::Malloc philos\n"), 1);
	if (ft_create_threads(philos, datos))
		return (1);
	ft_checking_philos(philos, &datos);
	ft_join_threads(philos, &datos);
	ft_free(philos, &datos);
	return (0);
}
