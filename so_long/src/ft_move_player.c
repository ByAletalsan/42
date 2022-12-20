/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 20:05:22 by atalaver          #+#    #+#             */
/*   Updated: 2022/12/20 00:11:06 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

t_obj	*ft_find_player(t_list *list)
{
	t_obj	*obj;

	while (list)
	{
		obj = list->content;
		if (obj->c == 'P')
			return (obj);
		list = list->next;
	}
	return (NULL);
}

static t_obj	*ft_can_move(t_list *list, int x, int y)
{
	t_obj	*obj;

	while (list)
	{
		obj = list->content;
		if (obj->c != 'P')
		{
			if (obj->x < x + 32 && obj->x + 64 > x + 32 &&
				obj->y < y && obj->y + 64 > y)
				return (obj);
			if (obj->x < x + 64 && obj->x + 64 > x + 64 &&
				obj->y < y + 32 && obj->y + 64 > y + 32)
				return (obj);
			if (obj->x < x + 32 && obj->x + 64 > x + 32 &&
				obj->y < y + 64 && obj->y + 64 > y + 64)
				return (obj);
			if (obj->x < x && obj->x + 64 > x && obj->y < y + 32 &&
				obj->y + 64 > y + 32)
				return (obj);
		}
		list = list->next;
	}
	return (NULL);
}

//Return 1 if the game is end, 0 continue
int	ft_move_right(t_game *game)
{
	t_obj	*player;
	t_obj	*obj_colision;

	player = ft_find_player(game->obj);
	obj_colision = ft_can_move(game->obj, player->x + VEL, player->y);
	if (!obj_colision && player->x + 62 + VEL < game->map.width * 64 - 64)
	{
		player->x += VEL;
		game->steps += 1;
	}
	else
	{
		if (obj_colision && obj_colision->c == 'C')
		{
			game->score -= 1;
			player->x += VEL;
			game->steps += 1;
			ft_rem_obj(game, obj_colision);
		}
		else if (obj_colision && obj_colision->c == 'E')
		{
			if (game->score <= 0)
			{
				mlx_destroy_window(game->vars.mlx, game->vars.win);
				exit(1);
			}
		}
	}
	return (0);
}

int	ft_move_left(t_game *game)
{
	t_obj	*player;
	t_obj	*obj_colision;

	player = ft_find_player(game->obj);
	obj_colision = ft_can_move(game->obj, player->x - VEL, player->y);
	if (!obj_colision && player->x - VEL > 62)
	{
		player->x -= VEL;
		game->steps += 1;
	}
	else
	{
		if (obj_colision && obj_colision->c == 'C')
		{
			game->score -= 1;
			player->x -= VEL;
			ft_rem_obj(game, obj_colision);
		}
		else if (obj_colision && obj_colision->c == 'E')
		{
			if (game->score <= 0)
			{
				mlx_destroy_window(game->vars.mlx, game->vars.win);
				exit(1);
			}
		}
	}
	return (0);
}

int	ft_move_top(t_game *game)
{
	t_obj	*player;
	t_obj	*obj_colision;

	player = ft_find_player(game->obj);
	obj_colision = ft_can_move(game->obj, player->x, player->y - VEL);
	if (!obj_colision && player->y - VEL > 62)
	{
		player->y -= VEL;
		game->steps += 1;
	}
	else
	{
		if (obj_colision && obj_colision->c == 'C')
		{
			game->score -= 1;
			player->y -= VEL;
			game->steps += 1;
			ft_rem_obj(game, obj_colision);
		}
		else if (obj_colision && obj_colision->c == 'E')
		{
			if (game->score <= 0)
			{
				mlx_destroy_window(game->vars.mlx, game->vars.win);
				exit(1);
			}
		}
	}
	return (0);
}

int	ft_move_down(t_game *game)
{
	t_obj	*player;
	t_obj	*obj_colision;

	player = ft_find_player(game->obj);
	obj_colision = ft_can_move(game->obj, player->x, player->y + VEL);
	if (!obj_colision && player->y + 62 + VEL < game->map.height * 64 - 64)
	{
		player->y += VEL;
		game->steps += 1;
	}
	else
	{
		if (obj_colision && obj_colision->c == 'C')
		{
			game->score -= 1;
			player->y += VEL;
			game->steps += 1;
			ft_rem_obj(game, obj_colision);
		}
		else if (obj_colision && obj_colision->c == 'E')
		{
			if (game->score <= 0)
			{
				mlx_destroy_window(game->vars.mlx, game->vars.win);
				exit(1);
			}
		}
	}
	return (0);
}
