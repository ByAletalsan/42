/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 14:35:55 by atalaver          #+#    #+#             */
/*   Updated: 2023/10/06 14:36:36 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	load_player(t_var *vars)
{
	vars->player.x = (vars->map->pos_x + 1) * SQ - (SQ / 2);
	vars->player.y = (vars->map->pos_y + 1) * SQ - (SQ / 2);
	vars->player.fov = (2 * MPI * 66) / 360;
	if (vars->map->orientation == 'N')
		vars->player.angle = MPI / 2;
	else if (vars->map->orientation == 'W')
		vars->player.angle = MPI;
	else if (vars->map->orientation == 'E')
		vars->player.angle = 0;
	else if (vars->map->orientation == 'S')
		vars->player.angle = MPI * 3 / 2;
	vars->tx.t_we = NULL;
	vars->tx.t_no = NULL;
	vars->tx.t_so = NULL;
	vars->tx.t_ea = NULL;
	vars->tx.t_kick0 = NULL;
	vars->tx.t_kick1 = NULL;
	vars->tx.t_door = NULL;
	vars->c_k = 0;
	vars->fr = 0;
	vars->fr_k = 0;
	vars->v_d = NULL;
	vars->c_d = 0;
}

void	free_data(t_var *vars)
{
	if (vars->tx.t_we)
		mlx_delete_texture(vars->tx.t_we);
	if (vars->tx.t_no)
		mlx_delete_texture(vars->tx.t_no);
	if (vars->tx.t_so)
		mlx_delete_texture(vars->tx.t_so);
	if (vars->tx.t_ea)
		mlx_delete_texture(vars->tx.t_ea);
	if (vars->tx.t_kick0)
		mlx_delete_texture(vars->tx.t_kick0);
	if (vars->tx.t_kick1)
		mlx_delete_texture(vars->tx.t_kick1);
	if (vars->tx.t_door)
		mlx_delete_texture(vars->tx.t_door);
	if (vars->c_d == 1 && vars->v_d)
		free (vars->v_d);
}

int	load_textures(t_var *vars)
{
	vars->tx.t_door = mlx_load_png("textures/door.png");
	if (!vars->tx.t_door)
		return (1);
	vars->tx.t_kick0 = mlx_load_png("textures/kick/kick0.png");
	vars->tx.t_kick1 = mlx_load_png("textures/kick/kick1.png");
	if (!vars->tx.t_kick0 || !vars->tx.t_kick1)
		return (1);
	vars->tx.t_we = mlx_load_png(vars->map->we);
	if (!vars->tx.t_we)
		return (1);
	vars->tx.t_no = mlx_load_png(vars->map->no);
	if (!vars->tx.t_no)
		return (1);
	vars->tx.t_so = mlx_load_png(vars->map->so);
	if (!vars->tx.t_so)
		return (1);
	vars->tx.t_ea = mlx_load_png(vars->map->ea);
	if (!vars->tx.t_ea)
		return (1);
	return (0);
}
