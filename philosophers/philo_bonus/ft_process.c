/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 16:27:37 by atalaver          #+#    #+#             */
/*   Updated: 2023/08/02 18:01:35 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_eat(t_philo *me)
{
	sem_wait(me->datos->forks);
	ft_print_action(me, ft_virtual_time(me->datos), "has taken a fork");
	sem_wait(me->datos->forks);
	ft_print_action(me, ft_virtual_time(me->datos), "has taken a fork");
	ft_print_action(me, ft_virtual_time(me->datos), "is eating");
	ft_msleep(me->datos, me->datos->time_to_eat);
	me->time_last_eat = ft_real_time();
	me->n_eat++;
	if (me->n_eat == me->datos->times)
	{
		me->datos->current_times++;
		printf("%d::%d ya!\n", me->datos->current_times, me->n_philo);
	}
	sem_post(me->datos->forks);
	sem_post(me->datos->forks);
}

void	*ft_vida(void *arg)
{
	t_philo		*me;
	pthread_t	check;

	me = (t_philo *)arg;
	pthread_create(&check, NULL, ft_check_philo, me);
	pthread_detach(check);
	while (1)
	{
		ft_eat(me);
		ft_print_action(me, ft_virtual_time(me->datos), "is sleeping");
		ft_msleep(me->datos, me->datos->time_to_sleep);
		ft_print_action(me, ft_virtual_time(me->datos), "is thinking");
	}
	return (NULL);
}

void	*ft_check_philo(void *arg)
{
	t_philo	*me;

	me = (t_philo *)arg;
	while (1)
	{
		sem_wait(me->datos->sem_check);
		if (ft_real_time() - me->time_last_eat > me->datos->time_to_die)
		{
			ft_print_action(me, ft_virtual_time(me->datos),
				"died");
			sem_post(me->datos->sem_stop);
			break ;
		}
		sem_post(me->datos->sem_check);
		if (me->datos->times != -1
			&& me->n_eat >= me->datos->times)
		{
			sem_post(me->datos->sem_stop);
			exit(0);
			break ;
		}
		usleep(10);
	}
	return (NULL);
}
