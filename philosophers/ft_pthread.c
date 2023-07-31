/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pthread.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 16:27:37 by atalaver          #+#    #+#             */
/*   Updated: 2023/07/31 20:38:41 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_print_action(t_philo *philo, unsigned long time, char *s)
{
	pthread_mutex_lock(&philo->datos->mutex_printf);
	printf("%lu %d %s\n", time, philo->n_philo, s);
	pthread_mutex_unlock(&philo->datos->mutex_printf);
}

static void	ft_msleep(t_dato *datos, unsigned long time)
{
	unsigned long	time_now;

	time_now = ft_real_time();
	while (!datos->end)
	{
		if (ft_real_time() - time_now >= time)
			return ;
		usleep(10);
	}
	return ;
}

static void	ft_eat_right(t_philo *me)
{
	pthread_mutex_lock(me->tenedor_right);
	ft_print_action(me, ft_virtual_time(me->datos), "has taken a fork");
	pthread_mutex_lock(me->tenedor_left);
	ft_print_action(me, ft_virtual_time(me->datos), "has taken a fork");
	ft_print_action(me, ft_virtual_time(me->datos), "is eating");
	ft_msleep(me->datos, me->datos->time_to_eat);
	pthread_mutex_lock(&me->mutex_time_lunch);
	me->time_last_eat = ft_real_time();
	me->n_eat++;
	pthread_mutex_unlock(&me->mutex_time_lunch);
	pthread_mutex_unlock(me->tenedor_right);
	pthread_mutex_unlock(me->tenedor_left);
}

static void	ft_eat_left(t_philo *me)
{
	usleep(50);
	pthread_mutex_lock(me->tenedor_left);
	ft_print_action(me, ft_virtual_time(me->datos), "has taken a fork");
	pthread_mutex_lock(me->tenedor_right);
	ft_print_action(me, ft_virtual_time(me->datos), "has taken a fork");
	ft_print_action(me, ft_virtual_time(me->datos), "is eating");
	ft_msleep(me->datos, me->datos->time_to_eat);
	pthread_mutex_lock(&me->mutex_time_lunch);
	me->time_last_eat = ft_real_time();
	me->n_eat++;
	pthread_mutex_unlock(&me->mutex_time_lunch);
	pthread_mutex_unlock(me->tenedor_right);
	pthread_mutex_unlock(me->tenedor_left);
}

static int	ft_is_end(t_dato *datos)
{
	int	end;

	pthread_mutex_lock(&datos->mutex_end);
	end = datos->end;
	pthread_mutex_unlock(&datos->mutex_end);
	return (end);
}

static void	*ft_vida(void *arg)
{
	t_philo	*me;

	me = (t_philo *)arg;
	while (1)
	{
		if (me->n_philo % 2)
			ft_eat_right(me);
		else
			ft_eat_left(me);
		if (ft_is_end(me->datos))
			break ;
		ft_print_action(me, ft_virtual_time(me->datos), "is sleeping");
		ft_msleep(me->datos, me->datos->time_to_sleep);
		if (ft_is_end(me->datos))
			break ;
		ft_print_action(me, ft_virtual_time(me->datos), "is thinking");
	}
	return (NULL);
}

void	ft_checking_philos(t_philo *philos, t_dato *datos)
{
	int	i;
	int	check_eats;

	while (1)
	{
		i = 0;
		check_eats = 0;
		while (i < datos->n_philos)
		{
			pthread_mutex_lock(&philos[i].mutex_time_lunch);
			if (ft_real_time() - philos[i].time_last_eat > datos->time_to_die)
			{
				ft_print_action(&philos[i], ft_virtual_time(philos[i].datos),
					"died");
				datos->end = 1;
				return ;
			}
			if (philos[i].n_eat >= datos->times)
				check_eats++;
			pthread_mutex_unlock(&philos[i].mutex_time_lunch);
			i++;
		}
		if (datos->times != -1 && check_eats == datos->n_philos)
		{
			datos->end = 1;
			return ;
		}
		usleep(10);
	}
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

int	ft_deteach_threads(t_philo *philos, t_dato *datos)
{
	int	error;
	int	i;

	i = 0;
	while (i < datos->n_philos)
	{
		error = pthread_detach(philos[i].thread);
		if (error)
			return (printf("Error::Join threads\n"), 1);
		i++;
	}
	return (0);
}
