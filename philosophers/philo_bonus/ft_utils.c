/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 16:24:36 by atalaver          #+#    #+#             */
/*   Updated: 2023/08/01 19:06:14 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*ft_create_philos(t_dato *datos)
{
	t_philo	*philos;
	int		n_philos;
	int		i;

	philos = (t_philo *)ft_calloc(datos->n_philos + 1, sizeof(t_philo));
	if (!philos)
		return (NULL);
	i = 1;
	while (i < datos->n_philos + 1)
	{
		philos[i - 1].n_philo = i;
		philos[i - 1].n_eat = 0;
		philos[i - 1].datos = datos;
		philos[i - 1].time_last_eat = datos->time_start;
		pthread_mutex_init(&philos[i - 1].mutex_time_lunch, NULL);
		philos[i - 1].tenedor_right = &datos->forks[i];
		if (i == 1)
			philos[i - 1].tenedor_left = &datos->forks[datos->n_philos];
		else
			philos[i - 1].tenedor_left = &datos->forks[i - 1];
		i++;
	}
	return (philos);
}

int	ft_load_datos(t_dato *datos, int argc, char **argv)
{
	datos->n_philos = ft_atoi(argv[1]);
	if (datos->n_philos == 0)
		return (1);
	datos->time_to_die = ft_atoi(argv[2]);
	if (datos->n_philos == 1)
	{
		printf("0 1 has taken a fork\n");
		usleep(datos->time_to_die * 1000);
		printf("%d 1 died\n", datos->time_to_die);
		return (1);
	}
	datos->time_to_eat = ft_atoi(argv[3]);
	datos->time_to_sleep = ft_atoi(argv[4]);
	datos->time_start = ft_real_time();
	datos->end = 0;
	pthread_mutex_init(&datos->mutex_printf, NULL);
	pthread_mutex_init(&datos->mutex_end, NULL);
	if (argc == 6)
		datos->times = ft_atoi(argv[5]);
	else
		datos->times = -1;
	return (0);
}

unsigned long	ft_real_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

unsigned long	ft_virtual_time(t_dato *datos)
{
	return (ft_real_time() - datos->time_start);
}

int	ft_is_end(t_dato *datos)
{
	int	end;

	pthread_mutex_lock(&datos->mutex_end);
	end = datos->end;
	pthread_mutex_unlock(&datos->mutex_end);
	return (end);
}