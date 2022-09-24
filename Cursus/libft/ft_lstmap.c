/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 11:18:56 by atalaver          #+#    #+#             */
/*   Updated: 2022/09/24 12:38:45 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_lstend(t_list *pr)
{
	free(pr->next);
	pr->next = NULL;
}

static t_list	*ft_clear(t_list **lst, void (*del)(void*))
{
	t_list	*p;
	t_list	*n;

	p = *lst;
	while (p != NULL)
	{
		n = p->next;
		ft_lstdelone(p, del);
		p = n;
	}
	*lst = NULL;
	return (NULL);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*r;
	t_list	*p;
	t_list	*pr;

	p = lst;
	if (!p)
		return (NULL);
	r = (t_list *)malloc(sizeof(t_list));
	if (!r)
		return (NULL);
	pr = r;
	while (p != NULL)
	{
		pr->content = f(p->content);
		pr->next = (t_list *)malloc(sizeof(t_list));
		if (!pr->next)
			return (ft_clear(&r, del));
		p = p->next;
		if (p == NULL)
			ft_lstend(pr);
		else
			pr = pr->next;
	}
	return (r);
}
