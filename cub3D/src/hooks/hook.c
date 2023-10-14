/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 14:28:20 by atalaver          #+#    #+#             */
/*   Updated: 2023/10/06 14:29:24 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

void	hook_camera(t_var *vars)
{
	if (mlx_is_key_down(vars->mlx, MLX_KEY_LEFT))
	{
		vars->player.angle += 0.05;
		if (vars->player.angle >= MPI * 2)
			vars->player.angle = vars->player.angle - MPI * 2;
		if (vars->v_d && vars->c_d)
			free(vars->v_d);
		vars->v_d = NULL;
		vars->c_d = 0;
	}
	else if (mlx_is_key_down(vars->mlx, MLX_KEY_RIGHT))
	{
		vars->player.angle -= 0.05;
		if (vars->player.angle < 0)
			vars->player.angle = MPI * 2 - vars->player.angle;
		if (vars->v_d && vars->c_d)
			free(vars->v_d);
		vars->v_d = NULL;
		vars->c_d = 0;
	}
}

void	hook_mouse(t_var *vars)
{
	mlx_get_mouse_pos(vars->mlx, &(vars->player.mx), &(vars->player.my));
	if (vars->player.mx < WIDTH / 2)
	{
		vars->player.angle += 0.05;
		if (vars->player.angle >= MPI * 2)
			vars->player.angle = vars->player.angle - MPI * 2;
		mlx_set_mouse_pos(vars->mlx, WIDTH / 2, HEIGHT / 2);
		if (vars->v_d && vars->c_d)
			free(vars->v_d);
		vars->v_d = NULL;
		vars->c_d = 0;
	}
	else if (vars->player.mx > WIDTH / 2)
	{
		vars->player.angle -= 0.05;
		if (vars->player.angle < 0)
			vars->player.angle = MPI * 2 - vars->player.angle;
		mlx_set_mouse_pos(vars->mlx, WIDTH / 2, HEIGHT / 2);
		if (vars->v_d && vars->c_d)
			free(vars->v_d);
		vars->v_d = NULL;
		vars->c_d = 0;
	}
}

static void	hook_kick_2(t_var *va)
{
	if (mlx_is_key_down(va->mlx, MLX_KEY_SPACE) && va->c_k == 0)
	{
		va->c_k = 1;
		va->fr_k = va->fr;
	}
}

void	hook_kick(t_var *va, t_vector *v)
{
	if (va->c_k == 2 && abs(va->fr - va->fr_k) >= 16)
	{
		mlx_delete_image(va->mlx, va->tx.i_kick);
		va->c_k = 0;
	}
	if (va->c_k == 1 && abs(va->fr - va->fr_k) >= 8)
	{
		va->c_k = 2;
		v = raycast(va, va->player.angle);
		if (v && v->c == 'P' && v->dist <= SQ)
			va->map->map[v->ym][v->xm] = 'D';
		else if (va->c_d && va->v_d && va->v_d->c == 'D' && va->v_d->dist <= SQ
			&& va->map->map[va->player.y / SQ][va->player.x / SQ] != 'D')
		{
			va->map->map[va->v_d->ym][va->v_d->xm] = 'P';
			if (va->v_d)
				free(va->v_d);
			va->c_d = 0;
		}
		if (v)
			free(v);
	}
	hook_kick_2(va);
}
