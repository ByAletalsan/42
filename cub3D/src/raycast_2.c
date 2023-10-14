/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 11:01:22 by atalaver          #+#    #+#             */
/*   Updated: 2023/10/06 14:49:53 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	vector_to_open_door_h(double rx, double ry, t_var *v)
{
	if (v->map->map[(int)((ry / SQ) - v->trash.c)][(int)(rx / SQ)] == 'D'
			&& fabs(v->trash.a_r - v->player.angle) <= MPI / 9)
	{
		if (v->v_d && v->c_d == 1)
			free (v->v_d);
		v->v_d = create_vector_horizontal(rx, ry, v);
		v->c_d = 1;
	}
}

void	vector_to_open_door_v(double rx, double ry, t_var *v)
{
	if (v->map->map[(int)(ry / SQ)][(int)((rx / SQ) - v->trash.c)] == 'D'
			&& fabs(v->trash.a_r - v->player.angle) <= MPI / 9)
	{
		if (v->v_d && v->c_d == 1)
			free (v->v_d);
		v->v_d = create_vector_vertical(rx, ry, v);
		v->c_d = 1;
	}
}

t_vector	*raycast(t_var *vars, double angle)
{
	t_vector	*vh;
	t_vector	*vv;

	vh = rays_horizontal(vars, angle);
	if (!vh)
		return (NULL);
	vv = rays_vertical(vars, angle);
	if (!vv)
		return (free(vh), NULL);
	if (vh->dist < vv->dist)
		return (free(vv), vh);
	else
		return (free(vh), vv);
	return (NULL);
}

t_vector	*create_vector_horizontal(double ray_x, double ray_y, t_var *vars)
{
	t_vector	*v;

	v = (t_vector *)malloc(sizeof(t_vector));
	if (!v)
		return (NULL);
	vars->trash.x = vars->player.x * SM;
	vars->trash.y = vars->player.y * SM;
	v->x = ray_x;
	v->y = ray_y;
	if (!check_limits_rays(ray_x, ray_y, vars))
	{
		v->xm = vars->player.x / SQ;
		v->ym = vars->player.y / SQ;
		v->c = '1';
	}
	else
	{
		v->c = vars->map->map[(int)((ray_y
					/ SQ) - vars->trash.c)][(int)(ray_x / SQ)];
		v->xm = (int)(ray_x / SQ);
		v->ym = (int)((ray_y / SQ) - vars->trash.c);
	}
	v->dist = sqrt((ray_x - vars->player.x) * (ray_x - vars->player.x)
			+ (ray_y - vars->player.y) * (ray_y - vars->player.y));
	return (v);
}

t_vector	*create_vector_vertical(double ray_x, double ray_y, t_var *vars)
{
	t_vector	*v;

	v = (t_vector *)malloc(sizeof(t_vector));
	if (!v)
		return (NULL);
	vars->trash.x = vars->player.x * SM;
	vars->trash.y = vars->player.y * SM;
	v->x = ray_x;
	v->y = ray_y;
	if (!check_limits_rays(ray_x, ray_y, vars))
	{
		v->xm = vars->player.x / SQ;
		v->ym = vars->player.y / SQ;
		v->c = '1';
	}
	else
	{
		v->c = vars->map->map[(int)(ray_y
				/ SQ)][(int)((ray_x / SQ) - vars->trash.c)];
		v->ym = (int)(ray_y / SQ);
		v->xm = (int)((ray_x / SQ) - vars->trash.c);
	}
	v->dist = sqrt((ray_x - vars->player.x) * (ray_x - vars->player.x)
			+ (ray_y - vars->player.y) * (ray_y - vars->player.y));
	return (v);
}
