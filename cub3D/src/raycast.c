/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 14:29:08 by dvasco-m          #+#    #+#             */
/*   Updated: 2023/10/06 11:13:28 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	check_limits_rays(double rx, double ry, t_var *v)
{
	return ((int)(ry / SQ) > 0 && (int)(rx / SQ) > 0
		&& (int)(ry / SQ) < (ft_len_matrix2(v->map->map))
		&& (int)(rx / SQ) < (int)(ft_strlen(v->map->map[(int)(ry / SQ)])));
}

static t_vector	*rays_horizontal_2(t_var *v, double angle, int x, int y)
{
	double	rx;
	double	ry;
	double	yn;
	double	xn;

	yn = ((int)(v->player.y / SQ + 1) * SQ - v->player.y);
	if (y < 0)
		yn = (v->player.y - (int)(v->player.y / SQ) * SQ);
	rx = v->player.x + (yn / tan(angle)) * x;
	ry = v->player.y + yn * y;
	xn = SQ / tan(angle);
	while (check_limits_rays(rx, ry, v)
		&& v->map->map[(int)((ry / SQ) - v->trash.c)][(int)(rx / SQ)] != '1'
		&& v->map->map[(int)((ry / SQ) - v->trash.c)][(int)(rx / SQ)] != 'P')
	{
		vector_to_open_door_h(rx, ry, v);
		rx += xn * x;
		ry += SQ * y;
		if (rx < 0)
			rx = 0;
		if (ry < 0)
			ry = 0;
	}
	return (create_vector_horizontal(rx, ry, v));
}

t_vector	*rays_horizontal(t_var *vars, double angle)
{
	vars->trash.c = 1;
	vars->trash.a_r = angle;
	if (angle < MPI / 2)
		return (rays_horizontal_2(vars, angle, 1, -1));
	else if (angle < MPI)
	{
		angle = MPI - angle;
		return (rays_horizontal_2(vars, angle, -1, -1));
	}
	else if (angle < MPI * 3 / 2)
	{
		angle = angle - MPI;
		vars->trash.c = 0;
		return (rays_horizontal_2(vars, angle, -1, 1));
	}
	else
	{
		angle = MPI * 2 - angle;
		vars->trash.c = 0;
		return (rays_horizontal_2(vars, angle, 1, 1));
	}
	return (NULL);
}

static t_vector	*rays_vertical_2(t_var *v, double angle, int x, int y)
{
	double		rx;
	double		ry;
	double		yn;
	double		xn;

	xn = ((int)(v->player.x / SQ + 1) * SQ - v->player.x);
	if (x < 0)
		xn = (v->player.x - (int)(v->player.x / SQ) * SQ);
	rx = v->player.x + xn * x;
	ry = v->player.y + (xn / tan(angle)) * y;
	yn = SQ / tan(angle);
	while (check_limits_rays(rx, ry, v)
		&& v->map->map[(int)(ry / SQ)][(int)((rx / SQ) - v->trash.c)] != '1'
		&& v->map->map[(int)(ry / SQ)][(int)((rx / SQ) - v->trash.c)] != 'P')
	{
		vector_to_open_door_v(rx, ry, v);
		rx += SQ * x;
		ry += yn * y;
		if (rx < 0)
			rx = 0;
		if (ry < 0)
			ry = 0;
	}
	return (create_vector_vertical(rx, ry, v));
}

t_vector	*rays_vertical(t_var *vars, double angle)
{
	vars->trash.c = 0;
	vars->trash.a_r = angle;
	if (angle < MPI / 2)
	{
		angle = MPI / 2 - angle;
		return (rays_vertical_2(vars, angle, 1, -1));
	}
	else if (angle < MPI)
	{
		angle = angle - MPI / 2;
		vars->trash.c = 1;
		return (rays_vertical_2(vars, angle, -1, -1));
	}
	else if (angle < MPI * 3 / 2)
	{
		angle = MPI * 3 / 2 - angle;
		vars->trash.c = 1;
		return (rays_vertical_2(vars, angle, -1, 1));
	}
	else
	{
		angle = angle - MPI * 3 / 2;
		return (rays_vertical_2(vars, angle, 1, 1));
	}
	return (NULL);
}
