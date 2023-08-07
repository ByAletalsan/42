/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 14:59:09 by atalaver          #+#    #+#             */
/*   Updated: 2023/08/02 17:43:55 by atalaver         ###   ########.fr       */
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
			return (printf("ERROR::Arg not is a number!\n"), 1);
		i++;
	}
	return (0);
}

static void	ft_free(t_philo *philos, t_dato *datos)
{
	int	i;

	i = 0;
	while (i < datos->n_philos)
	{
		kill(philos[i].pid, SIGKILL);
		i++;
	}
	sem_close(datos->sem_printf);
	sem_close(datos->forks);
	sem_close(datos->sem_stop);
	free(philos);
}

int	main(int argc, char **argv)
{
	t_dato			datos;
	t_philo			*philos;

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
	sem_wait(datos.sem_stop);
	ft_free(philos, &datos);
	return (0);
}
