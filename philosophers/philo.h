/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 15:02:42 by atalaver          #+#    #+#             */
/*   Updated: 2023/07/31 20:38:57 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

# define SEC 1000000

typedef struct datos
{
	int				n_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				times;
	int				end;
	unsigned long	time_start;
	pthread_mutex_t	*forks;
	pthread_mutex_t	mutex_printf;
	pthread_mutex_t	mutex_end;
}	t_dato;

typedef struct philo
{
	int				n_philo;
	pthread_t		thread;
	t_dato			*datos;
	int				n_eat;
	unsigned long	time_last_eat;
	pthread_mutex_t	mutex_time_lunch;
	pthread_mutex_t	*tenedor_left;
	pthread_mutex_t	*tenedor_right;
}	t_philo;

//Pthreads
int				ft_create_threads(t_philo *philos, t_dato datos);
int				ft_deteach_threads(t_philo *philos, t_dato *datos);
void			ft_checking_philos(t_philo *philos, t_dato *datos);
//Utils
t_philo			*ft_create_philos(t_dato *datos);
void			ft_load_datos(t_dato *datos, int argc, char **argv);
pthread_mutex_t	*ft_init_mutex(t_dato datos);
unsigned long	ft_real_time(void);
unsigned long	ft_virtual_time(t_dato *datos);
//Libft
void			*ft_calloc(size_t nmemb, size_t size);
int				ft_atoi(const char *str);
int				ft_is_number(char *s);

#endif