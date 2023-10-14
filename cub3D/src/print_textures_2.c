/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_textures_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvasco-m <dvasco-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 11:35:23 by atalaver          #+#    #+#             */
/*   Updated: 2023/10/06 22:13:31 by dvasco-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	print_kick(t_var *v)
{
	if (v->c_k == 1)
	{
		mlx_delete_image(v->mlx, v->tx.i_kick);
		v->tx.i_kick = mlx_texture_to_image(v->mlx, v->tx.t_kick0);
		mlx_image_to_window(v->mlx, v->tx.i_kick, WIDTH / 2,
			HEIGHT - v->tx.t_kick0->height);
	}
	if (v->c_k == 2)
	{
		mlx_delete_image(v->mlx, v->tx.i_kick);
		v->tx.i_kick = mlx_texture_to_image(v->mlx, v->tx.t_kick1);
		mlx_image_to_window(v->mlx, v->tx.i_kick, WIDTH / 2,
			HEIGHT - v->tx.t_kick1->height);
	}
}

//SOME UTILS
static void	valid_location_2(t_var *vars, char key, double *x, double *y)
{
	if (key == 'W')
	{
		*x = vars->player.x + (int)(round((SPEED + vars->trash.y)
					* cos(vars->player.angle)));
		*y = vars->player.y - (int)(round((SPEED + vars->trash.y)
					* sin(vars->player.angle)));
	}
	else if (key == 'S')
	{
		*x = vars->player.x - (int)(round((SPEED + vars->trash.y)
					* cos(vars->player.angle)));
		*y = vars->player.y + (int)(round((SPEED + vars->trash.y)
					* sin(vars->player.angle)));
	}
	else if (key == 'A')
	{
		*x = vars->player.x + (int)(round((SPEED + vars->trash.y)
					* cos(vars->player.angle + MPI / 2)));
		*y = vars->player.y - (int)(round((SPEED + vars->trash.y)
					* sin(vars->player.angle + MPI / 2)));
	}
}

int	valid_location(t_var *vars, char key)
{
	double			x;
	double			y;

	vars->trash.y = -2;
	while (++vars->trash.y <= 5)
	{
		valid_location_2(vars, key, &x, &y);
		if (key == 'D')
		{
			x = vars->player.x - (int)(round((SPEED + vars->trash.y)
						* cos(vars->player.angle + MPI / 2)));
			y = vars->player.y + (int)(round((SPEED + vars->trash.y)
						* sin(vars->player.angle + MPI / 2)));
		}
		if (vars->map->map[(int)(y / SQ)][(int)(x / SQ)] == '1'
				|| vars->map->map[(int)(y / SQ)][(int)(x / SQ)] == 'P')
			return (0);
	}
	return (1);
}
