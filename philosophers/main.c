/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 14:59:09 by atalaver          #+#    #+#             */
/*   Updated: 2023/02/05 17:02:16 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_inv_arg(char *s)
{
	printf("%s <number_of_philosophers> <time_to_die> ", s);
	printf("<time_to_eat> <time_to_eat> ");
	printf("[number_of_times_each_philosopher_must_eat]\n");
	exit(1);
}

static void	ft_free(int *tenedores, t_philo *philos)
{
	free(tenedores);
	free(philos);
}

int	main(int argc, char **argv)
{
	t_philo	*philos;
	int		*tenedores;
	t_dato	datos;
	int		error;

	if (argc != 5 && argc != 6)
		ft_inv_arg(argv[0]);
	ft_load_datos(&datos, argc, argv);
	tenedores = ft_calloc(argc - 1, sizeof(int));
	if (!tenedores)
		return (printf("Error::Malloc tenedores\n"), 1);
	philos = ft_create_philos(datos, tenedores);
	if (!philos)
		return (printf("Error::Malloc philos\n"), 1);
	error = ft_create_threads(philos);
	if (error)
		return (1);
	error = ft_join_threads(philos);
	if (error)
		return (ft_free(tenedores, philos), 1);
	ft_free(tenedores, philos);
	return (0);
}
