/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 14:59:09 by atalaver          #+#    #+#             */
/*   Updated: 2023/08/09 16:41:56 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_inv_arg(char *s)
{
	printf("%s <number_of_philosophers> <time_to_die> ", s);
	printf("<time_to_eat> <time_to_eat> ");
	printf("[number_of_times_each_philosopher_must_eat]\n");
}

static int	ft_check_arg(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (ft_is_number(argv[i]))
			return (printf("ERROR::Arg invalid!\n"), 1);
		i++;
	}
	return (0);
}

static void	ft_free(t_dato *datos)
{
	sem_close(datos->sem_printf);
	sem_unlink("sem_printf");
	sem_close(datos->forks);
	sem_unlink("forks");
	sem_post(datos->sem_stop);
	sem_close(datos->sem_stop);
	sem_unlink("sem_stop");
	sem_close(datos->sem_eat);
	sem_unlink("sem_eat");
}

void	*ft_check_dead(void *data)
{
	t_philo			*philos;
	int				i;

	philos = (t_philo *)data;
	i = 0;
	sem_wait(philos->datos->sem_stop);
	while (i < philos->datos->n_philos)
	{
		kill(philos[i].pid, SIGKILL);
		i++;
	}
	return (free(philos), NULL);
}

int	main(int argc, char **argv)
{
	t_dato			datos;
	t_philo			*philos;
	pthread_t		pt;
	int				i;

	if (argc != 5 && argc != 6)
		return (ft_inv_arg(argv[0]), 1);
	if (ft_check_arg(argc, argv))
		return (1);
	if (ft_load_datos(&datos, argc, argv))
		return (1);
	philos = ft_create_philos(&datos);
	if (!philos)
		return (printf("Error::Malloc philos\n"), 1);
	sem_wait(datos.sem_stop);
	ft_create_process(philos, datos);
	pthread_create(&pt, NULL, ft_check_dead, philos);
	pthread_detach(pt);
	i = 0;
	while (i++ < datos.n_philos)
		waitpid(-1, NULL, 0);
	ft_free(&datos);
	return (0);
}
