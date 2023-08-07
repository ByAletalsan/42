/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 16:24:36 by atalaver          #+#    #+#             */
/*   Updated: 2023/08/07 14:47:49 by atalaver         ###   ########.fr       */
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
	datos->time_to_eat = ft_atoi(argv[3]);
	datos->time_to_sleep = ft_atoi(argv[4]);
	datos->time_start = ft_real_time();
	datos->end = 0;
	sem_unlink("sem_printf");
	datos->sem_printf = sem_open("sem_printf", O_CREAT, 0600, 1);
	sem_unlink("forks");
	datos->forks = sem_open("forks", O_CREAT, 0600, datos->n_philos);
	sem_unlink("sem_stop");
	datos->sem_stop = sem_open("sem_stop", O_CREAT, 0600, 1);
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
