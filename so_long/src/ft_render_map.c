/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 09:40:13 by atalaver          #+#    #+#             */
/*   Updated: 2022/12/16 20:58:14 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	ft_print_border(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map.height)
	{
		j = 0;
		while (j < game->map.width)
		{
			if (i == 0 || i == game->map.height - 1)
				mlx_put_image_to_window(game->vars.mlx, game->vars.win,
					game->spr.wall.img, j * 64, i * 64);
			else
			{
				if (j == 0 || j == game->map.width - 1)
					mlx_put_image_to_window(game->vars.mlx, game->vars.win,
						game->spr.wall.img, j * 64, i * 64);
				else
					mlx_put_image_to_window(game->vars.mlx, game->vars.win,
						game->spr.floor.img, j * 64, i * 64);
			}
			j++;
		}
		i++;
	}
}

void	ft_print_obj(t_game *game)
{
	t_list	*o;
	t_obj	*obj;

	o = game->obj;
	while (o)
	{
		obj = o->content;
		if (obj->c == '1')
			mlx_put_image_to_window(game->vars.mlx, game->vars.win,
				game->spr.wall.img, obj->x, obj->y);
		else if (obj->c == 'C')
			mlx_put_image_to_window(game->vars.mlx, game->vars.win,
				game->spr.chest.img, obj->x, obj->y);
		else if (obj->c == 'P')
			mlx_put_image_to_window(game->vars.mlx, game->vars.win,
				game->spr.player.img, obj->x, obj->y);
		else if (obj->c == 'E')
		{
			mlx_put_image_to_window(game->vars.mlx, game->vars.win,
				game->spr.door[1].img, obj->x, obj->y);
			mlx_put_image_to_window(game->vars.mlx, game->vars.win,
				game->spr.door[0].img, obj->x, obj->y);
			if (game->score)
				mlx_put_image_to_window(game->vars.mlx, game->vars.win,
					game->spr.door[2].img, obj->x, obj->y);
			else
				mlx_put_image_to_window(game->vars.mlx, game->vars.win,
					game->spr.door[3].img, obj->x, obj->y);
		}
		o = o->next;
	}
}

//Renderizamos el mapa con los sprites correspondientes
void	ft_render_map(t_game *game)
{
	ft_print_border(game);
	ft_print_obj(game);
	mlx_string_put(game->vars.mlx, game->vars.win, 5, 15, 0x00000000,
		ft_strjoin("Score: ", ft_itoa(game->score)));
}
