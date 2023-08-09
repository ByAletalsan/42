/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pthread.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 16:27:37 by atalaver          #+#    #+#             */
/*   Updated: 2023/08/09 16:47:59 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_eat_right(t_philo *me)
{
	pthread_mutex_lock(me->tenedor_right);
	ft_print_action(me, ft_virtual_time(me->datos), "has taken a fork");
	if (me->datos->n_philos == 1)
	{
		ft_msleep(me->datos, me->datos->time_to_die + 100);
		return ;
	}
	pthread_mutex_lock(me->tenedor_left);
	ft_print_action(me, ft_virtual_time(me->datos), "has taken a fork");
	pthread_mutex_lock(&me->mutex_time_lunch);
	me->time_last_eat = ft_real_time();
	me->n_eat++;
	pthread_mutex_unlock(&me->mutex_time_lunch);
	ft_print_action(me, ft_virtual_time(me->datos), "is eating");
	ft_msleep(me->datos, me->datos->time_to_eat);
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

void	*ft_vida(void *arg)
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
			if (ft_check_died(philos, datos, &check_eats, i))
				return ;
			i++;
		}
		if (datos->times != -1 && check_eats == datos->n_philos)
		{
			pthread_mutex_lock(&datos->mutex_end);
			datos->end = 1;
			pthread_mutex_unlock(&datos->mutex_end);
			return ;
		}
		usleep(10);
	}
}
