/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 10:26:12 by atalaver          #+#    #+#             */
/*   Updated: 2022/11/23 12:40:09 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	t_mapa	map;
	t_vars	vars;

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
	//ft_printf("%s\n", map.mapa);
	if (ft_check_map(map.mapa))
	{
		ft_printf("Error\n");
		free(map.mapa);
		exit(1);
	}
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, map.width * 64, map.height * 64, "./so_long");
	ft_render_map(vars, map);
	mlx_loop(vars.mlx);
	free(map.mapa);
	return (0);
}
