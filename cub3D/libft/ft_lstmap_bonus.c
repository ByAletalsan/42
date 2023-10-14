/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvasco-m <dvasco-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 20:11:22 by dvasco-m          #+#    #+#             */
/*   Updated: 2022/09/30 18:37:31 by dvasco-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*lst_out;
	t_list	*actual;

	lst_out = NULL ;
	while (lst != NULL)
	{
		actual = ft_lstnew(f(lst->content));
		if (!actual)
		{
			ft_lstclear(&lst_out, del);
			return (NULL);
		}
		ft_lstadd_back(&lst_out, actual);
		lst = lst->next;
	}
	return (lst_out);
}
