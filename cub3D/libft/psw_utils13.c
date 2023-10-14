/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   psw_utils13.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvasco-m <dvasco-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 20:21:19 by dvasco-m          #+#    #+#             */
/*   Updated: 2023/01/26 20:21:26 by dvasco-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_ord2(t_stack *lstack_a)
{
	if (lstack_a->stack->number > lstack_a->stack->next->number)
		swap(&(lstack_a->stack), 'a');
}

t_stl	*ft_new_node(int number)
{
	t_stl	*node;

	node = (t_stl *)malloc(sizeof(t_stl));
	if (node == NULL)
		return (NULL);
	node->number = number;
	node->pos = 0;
	node->next = NULL;
	return (node);
}

int	ft_stacksize(t_stl *lst)
{
	int	i;

	i = 0;
	if (lst == NULL)
		return (0);
	while (lst->next != NULL)
	{
		i++;
		lst = lst->next;
	}
	return (i + 1);
}

t_stl	*ft_stacklast(t_stl *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

t_stl	*ft_stack2last(t_stl *lst)
{
	if (lst == NULL)
		return (NULL);
	if (lst->next == NULL)
		return (NULL);
	while ((lst->next)->next != NULL)
		lst = lst->next;
	return (lst);
}
