/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tx_ea.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 12:25:20 by atalaver          #+#    #+#             */
/*   Updated: 2023/10/11 17:07:25 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

static void	ea_tam_hight_height(t_var *v, t_vector *vc, double x_print, t_tx tx)
{
	tx.i = (((vc->y % SQ)) - SQ) * 4;
	while (tx.i < (int)v->tx.t_ea->height * (int)v->tx.t_ea->width
		* (int)v->tx.t_ea->bytes_per_pixel && tx.y < HEIGHT - 1)
	{
		tx.color = get_rgba(tx.c[tx.i], tx.c[tx.i + 1],
				tx.c[tx.i + 2], tx.c[tx.i + 3]);
		if (++tx.contador >= (int)v->tx.t_ea->width)
		{
			tx.z += tx.tam / (int)v->tx.t_ea->height;
			while (tx.p < tx.z && tx.y < HEIGHT - 1)
			{
				if (x_print >= 0 && x_print < WIDTH
					&& tx.y >= 0 && tx.y < HEIGHT)
					mlx_put_pixel(v->img, x_print, tx.y, tx.color);
				tx.y++;
				tx.p++;
			}
			tx.contador = 0;
		}
		tx.i += 4;
	}
}

static void	ea_tam_less_height(t_var *v, t_vector *vc, double x_print, t_tx tx)
{
	tx.color = get_rgba(tx.c[((vc->y % SQ)) * 4], tx.c[(((vc->y % SQ))
				* 4) + 1], tx.c[(((vc->y % SQ)) * 4) + 2],
			tx.c[(((vc->y % SQ)) * 4) + 3]);
	if (x_print >= 0 && x_print < WIDTH && tx.y >= 0 && tx.y < HEIGHT)
		mlx_put_pixel(v->img, x_print, tx.y++, tx.color);
	tx.i = ((vc->y % SQ)) * 4;
	while (tx.i < (int)v->tx.t_ea->height * (int)v->tx.t_ea->width
		* (int)v->tx.t_ea->bytes_per_pixel)
	{
		tx.color = get_rgba(tx.c[tx.i], tx.c[tx.i + 1],
				tx.c[tx.i + 2], tx.c[tx.i + 3]);
		if (++tx.contador >= (int)v->tx.t_ea->width)
		{
			tx.z += tx.tam / (int)v->tx.t_ea->height;
			while (tx.p < tx.z)
			{
				if (x_print >= 0 && x_print < WIDTH
					&& tx.y >= 0 && tx.y < HEIGHT)
					mlx_put_pixel(v->img, x_print, tx.y++, tx.color);
				tx.p++;
			}
			tx.contador = 0;
		}
		tx.i += 4;
	}
}

void	print_texture_ea(t_var *v, t_vector *vc, double x_print, double tam)
{
	t_tx	tx;

	tx.c = v->tx.t_ea->pixels;
	tx.tam = 2 * tam;
	if (tx.tam <= HEIGHT)
	{
		tx.y = (int)(HEIGHT / 2 - tx.tam / 2);
		tx.contador = -1;
		tx.z = tx.tam / (int)v->tx.t_ea->height;
		tx.p = 0;
		ea_tam_less_height(v, vc, x_print, tx);
	}
	else
	{
		tx.y = 0;
		tx.contador = -1;
		if (tx.tam > HEIGHT * (int)v->tx.t_we->height)
			tx.tam = HEIGHT * (int)v->tx.t_we->height;
		tx.z = (((tx.tam - HEIGHT) / 2) / (tx.tam / (int)v->tx.t_ea->height));
		tx.p = fabs((HEIGHT - tx.tam) / 2);
		ea_tam_hight_height(v, vc, x_print, tx);
	}
}
