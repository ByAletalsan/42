/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 20:05:22 by atalaver          #+#    #+#             */
/*   Updated: 2023/02/08 19:57:22 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

t_obj	*ft_can_move(t_list *list, int x, int y)
{
	t_obj	*obj;

	while (list)
	{
		obj = list->content;
		if (obj->c != 'P')
		{
			if (obj->x < x + 32 && obj->x + 64 > x + 32
				&& obj->y < y && obj->y + 64 > y)
				return (obj);
			if (obj->x < x + 64 && obj->x + 64 > x + 64
				&& obj->y < y + 32 && obj->y + 64 > y + 32)
				return (obj);
			if (obj->x < x + 32 && obj->x + 64 > x + 32
				&& obj->y < y + 64 && obj->y + 64 > y + 64)
				return (obj);
			if (obj->x < x && obj->x + 64 > x && obj->y < y + 32
				&& obj->y + 64 > y + 32)
				return (obj);
		}
		list = list->next;
	}
	return (NULL);
}

static int	ft_move_exit(t_game game, int x, int y)
{
	if (x < 64 || x > (game.map.width - 1) * 64 - 64)
		return (1);
	if (y < 64 || y > (game.map.height - 1) * 64 - 64)
		return (1);
	return (0);
}

static void	ft_collision(t_obj *obj_colision, t_obj *player,
	t_game *game, int *pos)
{
	if (obj_colision && obj_colision->c == 'C')
	{
		game->score -= 1;
		player->x += pos[0] * VEL;
		player->y += pos[1] * VEL;
		if (player->x % 64 == 0 && player->y % 64 == 0)
		{
			game->steps += 1;
			ft_printf("Steps:%i\n", game->steps);
		}
		ft_rem_obj(game, obj_colision);
	}
	else if (obj_colision && obj_colision->c == 'E')
	{
		if (game->score <= 0)
		{
			game->steps += 1;
			ft_printf("Steps:%i\n", game->steps);
			ft_printf("WIN!\n");
			ft_free_game(game);
		}
	}
}

//Move x,y -> 1, 0, -1
void	ft_move(t_game *game, int x, int y)
{
	t_obj	*player;
	t_obj	*obj_colision;
	int		pos[2];

	player = ft_find_player(game->obj);
	obj_colision = ft_can_move(game->obj, player->x + (x * VEL),
			player->y + (y * VEL));
	if (!obj_colision && !ft_move_exit(*game, player->x + (x * VEL),
			player->y + (y * VEL)))
	{
		player->x += x * VEL;
		player->y += y * VEL;
		if (player->x % 64 == 0 && player->y % 64 == 0)
		{
			game->steps += 1;
			ft_printf("Steps:%i\n", game->steps);
		}
	}
	else
	{
		pos[0] = x;
		pos[1] = y;
		ft_collision(obj_colision, player, game, pos);
	}
}
