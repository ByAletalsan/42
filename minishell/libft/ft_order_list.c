/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_order_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 20:16:32 by atalaver          #+#    #+#             */
/*   Updated: 2023/06/23 20:21:12 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_order_list(t_list *list)
{
	t_list	*aux;
	int		control;
	char	*aux_content;

	control = 1;
	while (control)
	{
		control = 0;
		aux = list;
		while (aux->next)
		{
			if (ft_strcmp(aux->content, aux->next->content) > 0)
			{
				aux_content = aux->content;
				aux->content = aux->next->content;
				aux->next->content = aux_content;
				control = 1;
				break ;
			}
			aux = aux->next;
		}
	}
}
