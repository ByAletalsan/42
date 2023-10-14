/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 14:31:13 by dvasco-m          #+#    #+#             */
/*   Updated: 2023/10/06 11:19:58 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static void	print_square(t_var *vars, int i, int j, uint32_t color)
{
	int	i2;
	int	j2;

	i2 = i;
	while (i2 < i + SQ * SM)
	{
		j2 = j;
		while (j2 < j + SQ * SM)
		{
			if (i2 == 0 || j2 == 0 || i2 == i + SQ * SM - 1
				|| j2 == j + SQ * SM - 1)
				mlx_put_pixel(vars->img, j2, i2, 0x000000ff);
			else
				mlx_put_pixel(vars->img, j2, i2, color);
			j2++;
		}
		i2++;
	}
}

static void	print_map(t_var *vars)
{
	int	i;
	int	j;

	i = 0;
	while (vars->map && vars->map->map[i])
	{
		j = 0;
		while (vars->map->map[i][j])
		{
			if (vars->map->map[i][j] == '1')
				print_square(vars, i * SQ * SM, j * SQ * SM, vars->map->c);
			else if (vars->map->map[i][j] == 'P'
						|| vars->map->map[i][j] == 'D')
				print_square(vars, i * SQ * SM, j * SQ * SM, vars->map->f);
			else
				print_square(vars, i * SQ * SM, j * SQ * SM, 0xffffffff);
			j++;
		}
		i++;
	}
}

static void	print_line(float x2, float y2, t_var *vars, uint32_t color)
{
	int		aux;
	float	m;
	float	i;
	float	j;

	if (vars->trash.x > x2)
	{
		aux = x2;
		x2 = vars->trash.x;
		vars->trash.x = aux;
		aux = y2;
		y2 = vars->trash.y;
		vars->trash.y = aux;
	}
	m = (y2 - vars->trash.y) / (x2 - vars->trash.x);
	i = vars->trash.x;
	j = vars->trash.y;
	while (i <= x2 && i >= 0 && i <= WIDTH && j >= 0 && j <= HEIGHT)
	{
		mlx_put_pixel(vars->img, i, j, color);
		j += m / 50;
		i += 0.02;
	}
}

void	print_background(t_var *vars)
{
	int	i;
	int	j;

	i = 0;
	while (i < HEIGHT / 2)
	{
		j = 0;
		while (j < WIDTH)
		{
			mlx_put_pixel(vars->img, j, i, vars->map->c);
			j++;
		}
		i++;
	}
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			mlx_put_pixel(vars->img, j, i, vars->map->f);
			j++;
		}
		i++;
	}
}

int	print_minimap(t_var *v, t_vector *vh, t_vector *vv)
{
	print_textures(v, NULL, NULL);
	print_map(v);
	v->trash.fy = v->player.angle - v->player.fov / 2;
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
		if (vh->dist < vv->dist)
			print_line(vh->x * SM, vh->y * SM, v, 0xff0000ff);
		else
			print_line(vv->x * SM, vv->y * SM, v, 0x00ff00ff);
		free(vh);
		free(vv);
		v->trash.fy += 0.005;
	}
	return (print_kick(v), 0);
}
