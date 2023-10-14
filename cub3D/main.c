/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 12:41:35 by atalaver          #+#    #+#             */
/*   Updated: 2023/10/06 15:18:59 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_leaks(void)
{
	system("leaks -q cub3D");
}

void	print_data_map(t_data_map *map)
{
	ft_printf("DATA_MAP!\n\n\n");
	ft_printf("NO: %s\n", map->no);
	ft_printf("SO: %s\n", map->so);
	ft_printf("WE: %s\n", map->we);
	ft_printf("EA: %s\n\n", map->ea);
	ft_printf("F: %u\n", map->f);
	ft_printf("C: %u\n\n", map->c);
	ft_printf("\n\n");
}

void	hooks(void *data)
{
	t_var		*vars;

	vars = (t_var *)data;
	if (vars->fr > 1000)
		vars->fr = 0;
	vars->fr += 1;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(vars->mlx);
		return ;
	}
	hooks_wasd(vars);
	hook_camera(vars);
	hook_mouse(vars);
	print_minimap(vars, NULL, NULL);
	hook_kick(vars, NULL);
}

int	load_mlx(t_var	*vars)
{
	vars->mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
	if (!(vars->mlx))
		return (printf("%s\n", mlx_strerror(mlx_errno)), 1);
	vars->img = mlx_new_image(vars->mlx, WIDTH, HEIGHT);
	if (!(vars->img))
		return (mlx_close_window(vars->mlx),
			printf("%s\n", mlx_strerror(mlx_errno)), 1);
	if (mlx_image_to_window(vars->mlx, vars->img, 0, 0) == -1)
		return (mlx_close_window(vars->mlx),
			printf("%s\n", mlx_strerror(mlx_errno)), 1);
	mlx_set_window_limit(vars->mlx, WIDTH, HEIGHT, WIDTH, HEIGHT);
	return (0);
}

int	main(int argc, char **argv)
{
	t_var		vars;

	atexit(ft_leaks);
	if (argc != 2)
		return (ft_printf("%s <map.cub>\n", argv[0]), 1);
	vars.map = load_map(argv[1]);
	if (!vars.map)
		return (1);
	if (load_mlx(&vars))
		return (1);
	load_player(&vars);
	print_data_map(vars.map);
	if (load_textures(&vars))
		return (free_data(&vars),
			free_map(vars.map), printf("Error\nLoad textures!\n"), 1);
	mlx_set_cursor_mode(vars.mlx, MLX_MOUSE_HIDDEN);
	mlx_set_window_title(vars.mlx, "POLLO DIABLO");
	mlx_loop_hook(vars.mlx, hooks, &vars);
	mlx_loop(vars.mlx);
	mlx_terminate(vars.mlx);
	free_map(vars.map);
	free_data(&vars);
	return (0);
}
