/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 21:16:13 by atalaver          #+#    #+#             */
/*   Updated: 2022/12/20 00:16:31 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	ft_rem_obj(t_game *game, t_obj *obj)
{
	t_list	*list;
	t_list	*ant;

	list = game->obj;
	ant = NULL;
	while (list)
	{
		if (list->content == obj)
		{
			if (game->obj == list)
				game->obj = list->next;
			else
			{
				ant->next = list->next;
				list->next = NULL;
			}
			free(list->content);
			free(list);
			break ;
		}
		ant = list;
		list = list->next;
	}
}

void	ft_free_sprites(t_game *game)
{
	mlx_destroy_image(game->vars.mlx, game->spr.chest.img);
	mlx_destroy_image(game->vars.mlx, game->spr.door[0].img);
	mlx_destroy_image(game->vars.mlx, game->spr.door[1].img);
	mlx_destroy_image(game->vars.mlx, game->spr.door[2].img);
	mlx_destroy_image(game->vars.mlx, game->spr.door[3].img);
	mlx_destroy_image(game->vars.mlx, game->spr.floor.img);
	mlx_destroy_image(game->vars.mlx, game->spr.player[0].img);
	mlx_destroy_image(game->vars.mlx, game->spr.player[1].img);
	mlx_destroy_image(game->vars.mlx, game->spr.player[2].img);
	mlx_destroy_image(game->vars.mlx, game->spr.player[3].img);
	mlx_destroy_image(game->vars.mlx, game->spr.wall.img);

	t_list	*list;
	t_list	*next;

	list = game->obj;
	while (list)
	{
		free(list->content);
		next = list->next;
		free(list);
		list = next;
	}
}
