/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 15:02:42 by atalaver          #+#    #+#             */
/*   Updated: 2023/02/05 16:38:14 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>

# define SEC 1000000

typedef struct datos
{
	int			n_philos;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			times;
}	t_dato;

typedef struct philo
{
	int			n_philo;
	pthread_t	thread;
	t_dato		datos;
	int			*tenedor_left;
	int			*tenedor_rigth;
}	t_philo;

//Pthreads
int		ft_create_threads(t_philo *philos);
int		ft_join_threads(t_philo *philos);
//Utils
t_philo	*ft_create_philos(t_dato datos, int *tenedores);
void	ft_print_philo(t_philo p);
void	ft_load_datos(t_dato *datos, int argc, char **argv);
//Libft
void	*ft_calloc(size_t nmemb, size_t size);
int		ft_atoi(const char *str);

#endif