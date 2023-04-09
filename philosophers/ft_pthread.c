/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pthread.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 16:27:37 by atalaver          #+#    #+#             */
/*   Updated: 2023/04/09 16:17:22 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_print_action(t_philo *philo, unsigned long time, char *s)
{
	pthread_mutex_lock(philo->mutex_printf);
	printf("%lu %d %s\n", time, philo->n_philo, s);
	pthread_mutex_unlock(philo->mutex_printf);
}

static void	*ft_vida(void	*arg)
{
	t_philo	*me;

	me = (t_philo *)arg;
	me->time_last_eat = ft_real_time();
	if (me->n_philo % 2 == 0)
		usleep(15000);
	me->time_last_eat = ft_real_time();
	while (1)
	{
		pthread_mutex_lock(me->tenedor_rigth);
		ft_print_action(me, ft_virtual_time(me->datos), "has taken a fork");
		pthread_mutex_lock(me->tenedor_left);
		ft_print_action(me, ft_virtual_time(me->datos), "has taken a fork");
		ft_print_action(me, ft_virtual_time(me->datos), "is eating");
		usleep(me->datos.time_to_eat * 1000);
		me->n_eat++;
		pthread_mutex_unlock(me->tenedor_rigth);
		pthread_mutex_unlock(me->tenedor_left);
		me->time_last_eat = ft_real_time();
		ft_print_action(me, ft_virtual_time(me->datos), "is sleeping");
		usleep(me->datos.time_to_sleep * 1000);
		ft_print_action(me, ft_virtual_time(me->datos), "is thinking");
	}
}

void	ft_checking_philos(t_philo *philos, t_dato datos)
{
	int	i;

	i = 0;
	while (1)
	{
		if (ft_real_time() - philos[i].time_last_eat > datos.time_to_die)
		{
			ft_print_action(&philos[i], ft_virtual_time(philos[i].datos),
				"died");
			exit(1);
			break ;
		}
		i++;
		if (i == datos.n_philos)
			i = 0;
		usleep(500);
	}
}

int	ft_create_threads(t_philo *philos)
{
	int	error;
	int	i;

	i = 0;
	while (i < philos->datos.n_philos)
	{
		error = pthread_create(&philos[i].thread, NULL, ft_vida, &philos[i]);
		if (error)
			return (printf("Error::Creat threads\n"), 1);
		i++;
	}
	return (0);
}

int	ft_join_threads(t_philo *philos)
{
	int	error;
	int	i;

	i = 0;
	while (i < philos->datos.n_philos)
	{
		error = pthread_join(philos[i].thread, NULL);
		if (error)
			return (printf("Error::Join threads\n"), 1);
		i++;
	}
	return (0);
}
