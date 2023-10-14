/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   psw_utils14.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvasco-m <dvasco-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 20:21:55 by dvasco-m          #+#    #+#             */
/*   Updated: 2023/01/26 20:22:05 by dvasco-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_add_node_back(t_stl **lst, t_stl *new)
{
	t_stl	*last;

	if (*lst != NULL)
	{
		last = ft_stacklast(*lst);
		last->next = new;
	}
	else
	{
		*lst = new;
	}
}

void	ft_add_node_front(t_stl **lst, t_stl *new)
{
	new->next = *lst;
	*lst = new;
}

void	ft_del_node_back(t_stl **lst)
{
	t_stl	*last;

	if (*lst != NULL)
	{
		last = ft_stacklast(*lst);
		free(last);
	}
}

void	ft_del_node_front(t_stl **lst)
{
	t_stl	*first;

	if (*lst != NULL)
	{
		first = *lst;
		*lst = first->next;
		free(first);
	}
}

void	ft_free_stack(t_stl **lst)
{
	while (*lst != NULL)
		ft_del_node_front(lst);
}
