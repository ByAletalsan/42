/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 21:16:13 by atalaver          #+#    #+#             */
/*   Updated: 2022/12/16 19:17:21 by atalaver         ###   ########.fr       */
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
			ant->next = list->next;
			list->next = NULL;
			free(list->content);
			free(list);
			break ;
		}
		ant = list;
		list = list->next;
	}
}
