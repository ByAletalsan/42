/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 15:34:24 by atalaver          #+#    #+#             */
/*   Updated: 2023/08/02 13:50:54 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print_action(t_philo *philo, unsigned long time, char *s)
{
	sem_wait(philo->datos->sem_printf);
	printf("%lu %d %s\n", time, philo->n_philo, s);
	sem_post(philo->datos->sem_printf);
}

void	ft_msleep(t_dato *datos, unsigned long time)
{
	unsigned long	time_now;

	time_now = ft_real_time();
	while (ft_real_time() - time_now < time)
		usleep(10);
	return ;
}

void	ft_create_process(t_philo *philos, t_dato datos)
{
	int	i;

	i = 0;
	while (i < datos.n_philos)
	{
		philos[i].pid = fork();
		if (philos[i].pid == 0)
		{
			ft_vida(&philos[i]);
			exit(0);
		}
		i++;
		usleep(100);
	}
}
