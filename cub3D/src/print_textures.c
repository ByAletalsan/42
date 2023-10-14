/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvasco-m <dvasco-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 10:59:29 by atalaver          #+#    #+#             */
/*   Updated: 2023/10/06 22:21:28 by dvasco-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static void	vh_less(t_vector *vh, double screen_x, t_var *v)
{
	if (vh->c == '1')
	{
		if (v->trash.fx <= MPI)
			print_texture_no(v, vh, screen_x, (40 * HEIGHT)
				/ (vh->dist * cos(v->trash.fy - v->player.angle)));
		else
			print_texture_so(v, vh, screen_x, (40 * HEIGHT)
				/ (vh->dist * cos(v->trash.fy - v->player.angle)));
	}
	else if (vh->c == 'P')
		print_texture_door_h(v, vh, screen_x, (40 * HEIGHT)
			/ (vh->dist * cos(v->trash.fy - v->player.angle)));
}

static void	vv_less(t_vector *vv, double screen_x, t_var *v)
{
	if (vv->c == '1')
	{
		if (v->trash.fx >= MPI / 2 && v->trash.fx <= 3 * MPI / 2)
			print_texture_we(v, vv, screen_x, (40 * HEIGHT)
				/ (vv->dist * cos(v->trash.fy - v->player.angle)));
		else
			print_texture_ea(v, vv, screen_x, (40 * HEIGHT)
				/ (vv->dist * cos(v->trash.fy - v->player.angle)));
	}
	else if (vv->c == 'P')
		print_texture_door_v(v, vv, screen_x, (40 * HEIGHT)
			/ (vv->dist * cos(v->trash.fy - v->player.angle)));
}

static void	vh_equal_vv(t_vector *vv, t_vector *vh, double z, t_var *v)
{
	double	screen_x;

	screen_x = WIDTH - (WIDTH / v->player.fov * z);
	if (v->trash.fx >= MPI / 2 - 0.005 && v->trash.fx <= MPI * 3 / 2)
	{
		if (vh->c == '1')
			print_texture_so(v, vh, screen_x, (40 * HEIGHT)
				/ (vh->dist * cos(v->trash.fy - v->player.angle)));
		else if (vh->c == 'P')
			print_texture_door_h(v, vh, screen_x, (40 * HEIGHT)
				/ (vh->dist * cos(v->trash.fy - v->player.angle)));
	}
	else if (v->trash.fx >= 0 && v->trash.fx <= MPI / 2)
	{
		if (vv->c == '1')
			print_texture_ea(v, vv, screen_x, (40 * HEIGHT)
				/ (vv->dist * cos(v->trash.fy - v->player.angle)));
		else if (vv->c == 'P')
			print_texture_door_v(v, vv, screen_x, (40 * HEIGHT)
				/ (vv->dist * cos(v->trash.fy - v->player.angle)));
	}
}

static void	print_side(t_vector *vv, t_vector *vh, double z, t_var *v)
{
	double	screen_x;

	screen_x = WIDTH - (WIDTH / v->player.fov * z);
	if (vh->dist == vv->dist)
		vh_equal_vv(vv, vh, z, v);
	else if (vh->dist < vv->dist)
		vh_less(vh, screen_x, v);
	else
		vv_less(vv, screen_x, v);
}

int	print_textures(t_var *v, t_vector *vh, t_vector *vv)
{
	double	z;

	print_background(v);
	v->trash.fy = v->player.angle - v->player.fov / 2;
	z = 0;
	while (v->trash.fy < v->player.angle + v->player.fov / 2)
	{
		v->trash.fx = v->trash.fy;
		if (v->trash.fy < 0)
			v->trash.fx = MPI * 2 + v->trash.fy;
		if (v->trash.fy > MPI * 2)
			v->trash.fx = v->trash.fy - MPI * 2;
		vh = rays_horizontal(v, v->trash.fx);
		if (!vh)
			return (1);
		vv = rays_vertical(v, v->trash.fx);
		if (!vv)
			return (free(vh), 1);
		print_side(vv, vh, z, v);
		free(vh);
		free(vv);
		z += 0.001;
		v->trash.fy += 0.001;
	}
	return (0);
}
