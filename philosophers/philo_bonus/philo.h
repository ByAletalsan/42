/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 15:02:42 by atalaver          #+#    #+#             */
/*   Updated: 2023/08/01 19:13:02 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <semaphore.h>
# include <sys/stat.h>
# include <fcntl.h>

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
int				ft_join_threads(t_philo *philos, t_dato *datos);
void			ft_checking_philos(t_philo *philos, t_dato *datos);
void			*ft_vida(void *arg);
//Utils
t_philo			*ft_create_philos(t_dato *datos);
int				ft_load_datos(t_dato *datos, int argc, char **argv);
pthread_mutex_t	*ft_init_mutex(t_dato datos);
unsigned long	ft_real_time(void);
unsigned long	ft_virtual_time(t_dato *datos);
void			ft_msleep(t_dato *datos, unsigned long time);
void			ft_print_action(t_philo *philo, unsigned long time, char *s);
int				ft_check_died(t_philo *philos, t_dato *datos, int *check_eats,
					int i);
int				ft_is_end(t_dato *datos);
//Libft
void			*ft_calloc(size_t nmemb, size_t size);
int				ft_atoi(const char *str);
int				ft_is_number(char *s);

#endif