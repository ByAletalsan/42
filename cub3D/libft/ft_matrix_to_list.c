/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_to_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvasco-m <dvasco-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 17:58:17 by dvasco-m          #+#    #+#             */
/*   Updated: 2023/06/02 17:02:29 by dvasco-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_content_lst(void *content)
{
	free(content);
}

t_list	*matrix_to_list(void **matrix)
{
	t_list	*lista;
	t_list	*aux;
	char	*cont;
	int		i;

	i = 0;
	lista = NULL;
	while (matrix[i])
	{
		cont = ft_strdup(matrix[i]);
		if (!cont)
			return (ft_lstclear(&lista, free_content_lst), NULL);
		aux = ft_lstnew(cont);
		if (!aux)
			return (free(cont), ft_lstclear(&lista, free_content_lst), NULL);
		ft_lstadd_back(&lista, aux);
		i++;
	}
	return (lista);
}

void	print_list(t_list	*lista)
{
	while (lista)
	{
		printf("%s\n", (char *)lista->content);
		lista = lista->next;
	}
}
