/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 10:26:12 by atalaver          #+#    #+#             */
/*   Updated: 2022/11/22 13:17:23 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	char	*map;

	if (argc != 2)
	{
		perror("Numero incorrecto de argumentos");
		exit(1);
	}
	if (!ft_check_ber(argv[1]))
		map = ft_read_map(argv[1]);
	else
	{
		ft_printf("Error\n");
		exit(1);
	}
	ft_printf("%s\n", map);
	if (ft_check_map(map))
	{
		ft_printf("Error\n");
		free(map);
		exit(1);
	}
	free(map);
	return (0);
}
