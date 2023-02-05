/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pthread.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 16:27:37 by atalaver          #+#    #+#             */
/*   Updated: 2023/02/05 17:02:25 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*ft_vida(void	*arg)
{
	t_philo	*me;

	me = (t_philo *)arg;
	printf("Philo No:%i\n", me->n_philo);
	printf("Tenedor left:%x\n", me->tenedor_left);
	printf("Tenedor rigth:%x\n\n", me->tenedor_rigth);
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
