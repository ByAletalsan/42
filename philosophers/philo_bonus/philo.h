/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 15:02:42 by atalaver          #+#    #+#             */
/*   Updated: 2023/08/07 14:44:16 by atalaver         ###   ########.fr       */
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
# include <signal.h>

typedef struct datos
{
	int				n_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				times;
	int				end;
	unsigned long	time_start;
	sem_t			*forks;
	sem_t			*sem_printf;
	sem_t			*sem_stop;
}	t_dato;

typedef struct philo
{
	int				n_philo;
	pid_t			pid;
	t_dato			*datos;
	int				n_eat;
	unsigned long	time_last_eat;
}	t_philo;

//Process
void			ft_create_process(t_philo *philos, t_dato datos);
void			*ft_check_philo(void *arg);
void			*ft_vida(void *arg);
//Utils
t_philo			*ft_create_philos(t_dato *datos);
int				ft_load_datos(t_dato *datos, int argc, char **argv);
unsigned long	ft_real_time(void);
unsigned long	ft_virtual_time(t_dato *datos);
void			ft_msleep(t_dato *datos, unsigned long time);
void			ft_print_action(t_philo *philo, unsigned long time, char *s);
//Libft
void			*ft_calloc(size_t nmemb, size_t size);
int				ft_atoi(const char *str);
int				ft_is_number(char *s);

#endif