/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render_map_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 09:40:13 by atalaver          #+#    #+#             */
/*   Updated: 2023/02/08 20:28:06 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	ft_reset_frames(t_game *game)
{
	game->frame += 1;
	if (game->frame == 20)
	{
		if (game->frame_enemi == 3)
			game->frame_enemi = 0;
		else
			game->frame_enemi++;
		game->frame = 0;
	}
}

static void	ft_print_border(t_game *game)
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

static void	ft_print_door(t_game *game, t_obj *obj)
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

static void	ft_print_obj(t_game *game)
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
				game->spr.player[game->direction - 1].img, obj->x, obj->y);
		else if (obj->c == 'X')
			mlx_put_image_to_window(game->vars.mlx, game->vars.win,
				game->spr.enemi[game->frame_enemi].img, obj->x, obj->y);
		else if (obj->c == 'E')
			ft_print_door(game, obj);
		o = o->next;
	}
}

//Renderizamos el mapa con los sprites correspondientes
void	ft_render_map(t_game *game)
{
	char	*steps;

	ft_print_border(game);
	ft_print_obj(game);
	mlx_string_put(game->vars.mlx, game->vars.win, 20, 20, 0x000000, "Steps: ");
	steps = ft_itoa(game->steps);
	mlx_string_put(game->vars.mlx, game->vars.win, 70, 20, 0x000000, steps);
	free(steps);
}
