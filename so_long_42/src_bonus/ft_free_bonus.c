/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 19:36:01 by atalaver          #+#    #+#             */
/*   Updated: 2023/02/08 20:16:14 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	ft_free_enemi_spr(t_game *game)
{
	mlx_destroy_image(game->vars.mlx, game->spr.enemi[0].img);
	mlx_destroy_image(game->vars.mlx, game->spr.enemi[1].img);
	mlx_destroy_image(game->vars.mlx, game->spr.enemi[2].img);
	mlx_destroy_image(game->vars.mlx, game->spr.enemi[3].img);
}

static void	ft_free_sprites(t_game *game)
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
}

void	ft_free_obj(t_game *game)
{
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

static void	ft_leaks(void)
{
	system("leaks so_long");
}

int	ft_free_game(t_game *game)
{
	free(game->map.mapa);
	ft_free_sprites(game);
	ft_free_enemi_spr(game);
	ft_free_obj(game);
	mlx_clear_window(game->vars.mlx, game->vars.win);
	mlx_destroy_window(game->vars.mlx, game->vars.win);
	atexit(ft_leaks);
	exit(0);
}
