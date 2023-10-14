/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_to_matrix.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 20:46:28 by atalaver          #+#    #+#             */
/*   Updated: 2023/09/19 21:05:54 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**list_to_matrix(t_list *list)
{
	char	**result;
	int		i;

	result = (char **)malloc((ft_len_list(list) + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	i = 0;
	while (list)
	{
		result[i] = ft_strdup(list->content);
		if (!result[i])
			return (ft_free_params(result), NULL);
		list = list->next;
		i++;
	}
	result[i] = NULL;
	return (result);
}
