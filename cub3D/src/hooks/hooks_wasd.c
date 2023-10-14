/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_wasd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 14:31:56 by atalaver          #+#    #+#             */
/*   Updated: 2023/10/06 14:44:20 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

static void	hook_w(t_var *vars)
{
	double	x;
	double	y;

	x = vars->player.x + (int)round((SPEED + 10) * cos(vars->player.angle));
	y = vars->player.y - (int)round((SPEED + 10) * sin(vars->player.angle));
	if ((int)(x / SQ) > 0 && (int)(y / SQ) > 0
		&& (int)(y / SQ) < ft_len_matrix2(vars->map->map)
		&& (int)(x / SQ) < (int)ft_strlen(vars->map->map[(int)(y / SQ)])
		&& (vars->map->map[(int)(y / SQ)][(int)(x / SQ)] != '1'
		&& (vars->map->map[(int)(y / SQ)][(int)(x / SQ)] != 'P'
		&& valid_location(vars, 'W'))))
	{
		vars->player.x += (int)round(SPEED * cos(vars->player.angle));
		vars->player.y -= (int)round(SPEED * sin(vars->player.angle));
		if (vars->v_d && vars->c_d)
			free(vars->v_d);
		vars->v_d = NULL;
		vars->c_d = 0;
	}
}

static void	hook_s(t_var *vars)
{
	double	x;
	double	y;

	x = vars->player.x - (int)round((SPEED + 10) * cos(vars->player.angle));
	y = vars->player.y + (int)round((SPEED + 10) * sin(vars->player.angle));
	if ((int)(x / SQ) > 0 && (int)(y / SQ) > 0
		&& (int)(y / SQ) < ft_len_matrix2(vars->map->map)
		&& (int)(x / SQ) < (int)ft_strlen(vars->map->map[(int)(y / SQ)])
		&& (vars->map->map[(int)(y / SQ)][(int)(x / SQ)] != '1'
		&& (vars->map->map[(int)(y / SQ)][(int)(x / SQ)] != 'P'
		&& valid_location(vars, 'S'))))
	{
		vars->player.x -= (int)round(SPEED * cos(vars->player.angle));
		vars->player.y += (int)round(SPEED * sin(vars->player.angle));
		if (vars->v_d && vars->c_d)
			free(vars->v_d);
		vars->v_d = NULL;
		vars->c_d = 0;
	}
}

static void	hook_a(t_var *vars)
{
	double	x;
	double	y;

	x = vars->player.x + (int)round((SPEED + 10)
			* cos(vars->player.angle + MPI / 2));
	y = vars->player.y - (int)round((SPEED + 10)
			* sin(vars->player.angle + MPI / 2));
	if ((int)(x / SQ) > 0 && (int)(y / SQ) > 0
		&& (int)(y / SQ) < ft_len_matrix2(vars->map->map)
		&& (int)(x / SQ) < (int)ft_strlen(vars->map->map[(int)(y / SQ)])
		&& (vars->map->map[(int)(y / SQ)][(int)(x / SQ)] != '1'
		&& (vars->map->map[(int)(y / SQ)][(int)(x / SQ)] != 'P'
		&& valid_location(vars, 'A'))))
	{
		vars->player.x += (int)round((SPEED)
				* cos(vars->player.angle + MPI / 2));
		vars->player.y -= (int)round((SPEED)
				* sin(vars->player.angle + MPI / 2));
		if (vars->v_d && vars->c_d)
			free(vars->v_d);
		vars->v_d = NULL;
		vars->c_d = 0;
	}
}

static void	hook_d(t_var *vars)
{
	double	x;
	double	y;

	x = vars->player.x - (int)round((SPEED + 10)
			* cos(vars->player.angle + MPI / 2));
	y = vars->player.y + (int)round((SPEED + 10)
			* sin(vars->player.angle + MPI / 2));
	if ((int)(x / SQ) > 0 && (int)(y / SQ) > 0
		&& (int)(y / SQ) < ft_len_matrix2(vars->map->map)
		&& (int)(x / SQ) < (int)ft_strlen(vars->map->map[(int)(y / SQ)])
		&& (vars->map->map[(int)(y / SQ)][(int)(x / SQ)] != '1'
		&& (vars->map->map[(int)(y / SQ)][(int)(x / SQ)] != 'P'
		&& valid_location(vars, 'D'))))
	{
		vars->player.x -= (int)round(SPEED * cos(vars->player.angle + MPI / 2));
		vars->player.y += (int)round(SPEED * sin(vars->player.angle + MPI / 2));
		if (vars->v_d && vars->c_d)
			free(vars->v_d);
		vars->v_d = NULL;
		vars->c_d = 0;
	}
}

void	hooks_wasd(t_var *vars)
{
	if (mlx_is_key_down(vars->mlx, MLX_KEY_W))
		hook_w(vars);
	else if (mlx_is_key_down(vars->mlx, MLX_KEY_S))
		hook_s(vars);
	else if (mlx_is_key_down(vars->mlx, MLX_KEY_A))
		hook_a(vars);
	else if (mlx_is_key_down(vars->mlx, MLX_KEY_D))
		hook_d(vars);
}
