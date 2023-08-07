/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 15:34:24 by atalaver          #+#    #+#             */
/*   Updated: 2023/08/07 20:15:41 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print_action(t_philo *philo, unsigned long time, char *s)
{
	pthread_mutex_lock(&philo->datos->mutex_printf);
	if (!ft_is_end(philo->datos))
	{
		printf("%lu %d %s\n", time, philo->n_philo, s);
	}
	pthread_mutex_unlock(&philo->datos->mutex_printf);
}

void	ft_msleep(t_dato *datos, unsigned long time)
{
	unsigned long	time_now;

	time_now = ft_real_time();
	while (1)
	{
		if (ft_is_end(datos))
			return ;
		if (ft_real_time() - time_now >= time)
			return ;
		usleep(10);
	}
	return ;
}

int	ft_create_threads(t_philo *philos, t_dato datos)
{
	int	error;
	int	i;

	i = 0;
	while (i < datos.n_philos)
	{
		error = pthread_create(&philos[i].thread, NULL, ft_vida, &philos[i]);
		if (error)
			return (printf("Error::Creat threads\n"), 1);
		i++;
	}
	return (0);
}

int	ft_join_threads(t_philo *philos, t_dato *datos)
{
	int	error;
	int	i;

	i = 0;
	while (i < datos->n_philos)
	{
		error = pthread_join(philos[i].thread, NULL);
		if (error)
			return (printf("Error::Join threads\n"), 1);
		i++;
	}
	return (0);
}

int	ft_check_died(t_philo *philos, t_dato *datos, int *check_eats, int i)
{
	pthread_mutex_lock(&philos[i].mutex_time_lunch);
	if (ft_real_time() - philos[i].time_last_eat > datos->time_to_die)
	{
		ft_print_action(&philos[i], ft_virtual_time(philos[i].datos),
			"died");
		pthread_mutex_lock(&datos->mutex_end);
		datos->end = 1;
		pthread_mutex_unlock(&datos->mutex_end);
		pthread_mutex_unlock(&philos[i].mutex_time_lunch);
		return (1);
	}
	if (philos[i].n_eat >= datos->times)
		*check_eats += 1;
	pthread_mutex_unlock(&philos[i].mutex_time_lunch);
	return (0);
}
