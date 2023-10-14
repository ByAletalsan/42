/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tx_so.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvasco-m <dvasco-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 12:08:31 by atalaver          #+#    #+#             */
/*   Updated: 2023/10/06 22:27:15 by dvasco-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

static void	so_tam_hight_height(t_var *v, t_vector *vc, double x_print, t_tx tx)
{
	tx.i = (SQ - (vc->x % SQ) - SQ) * 4;
	while (tx.i < (int)v->tx.t_so->height * (int)v->tx.t_so->width
		* (int)v->tx.t_so->bytes_per_pixel && tx.y < HEIGHT - 1)
	{
		tx.color = get_rgba(tx.c[tx.i], tx.c[tx.i + 1],
				tx.c[tx.i + 2], tx.c[tx.i + 3]);
		if (++tx.contador >= (int)v->tx.t_so->width)
		{
			tx.z += tx.tam / (int)v->tx.t_so->height;
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

static void	so_tam_less_height(t_var *v, t_vector *vc, double x_print, t_tx tx)
{
	tx.color = get_rgba(tx.c[(SQ - (vc->x % SQ)) * 4], tx.c[((SQ - (vc->x % SQ))
				* 4) + 1], tx.c[((SQ - (vc->x % SQ)) * 4) + 2],
			tx.c[((SQ - (vc->x % SQ)) * 4) + 3]);
	if (x_print >= 0 && x_print < WIDTH && tx.y >= 0 && tx.y < HEIGHT)
		mlx_put_pixel(v->img, x_print, tx.y++, tx.color);
	tx.i = (SQ - (vc->x % SQ)) * 4;
	while (tx.i < (int)v->tx.t_so->height * (int)v->tx.t_so->width
		* (int)v->tx.t_so->bytes_per_pixel && tx.y < HEIGHT - 1)
	{
		tx.color = get_rgba(tx.c[tx.i], tx.c[tx.i + 1],
				tx.c[tx.i + 2], tx.c[tx.i + 3]);
		if (++tx.contador >= (int)v->tx.t_so->width)
		{
			tx.z += tx.tam / (int)v->tx.t_so->height;
			while (tx.p < tx.z && tx.y < HEIGHT - 1)
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

void	print_texture_so(t_var *v, t_vector *vc, double x_print, double tam)
{
	t_tx	tx;

	tx.c = v->tx.t_so->pixels;
	tx.tam = 2 * tam;
	if (tx.tam <= HEIGHT)
	{
		tx.y = (int)(HEIGHT / 2 - tx.tam / 2);
		tx.contador = -1;
		tx.z = tx.tam / (int)v->tx.t_so->height;
		tx.p = 0;
		so_tam_less_height(v, vc, x_print, tx);
	}
	else
	{
		tx.y = 0;
		tx.contador = -1;
		if (tx.tam > HEIGHT * (int)v->tx.t_we->height)
			tx.tam = HEIGHT * (int)v->tx.t_we->height;
		tx.z = (((tx.tam - HEIGHT) / 2) / (tx.tam / (int)v->tx.t_so->height));
		tx.p = fabs((HEIGHT - tx.tam) / 2);
		so_tam_hight_height(v, vc, x_print, tx);
	}
}
