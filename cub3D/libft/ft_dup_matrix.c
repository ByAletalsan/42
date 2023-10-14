/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dup_matrix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvasco-m <dvasco-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 17:56:16 by dvasco-m          #+#    #+#             */
/*   Updated: 2023/09/21 17:59:18 by dvasco-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_dup_matrix(char **matrix)
{
	char	**dup;
	int		i;
	int		len;

	len = ft_len_matrix2(matrix);
	dup = (char **)malloc((len + 1) * sizeof(char *));
	if (!dup)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dup[i] = ft_strdup(matrix[i]);
		if (!dup[i])
			return (ft_free_params(dup), NULL);
		i++;
	}
	dup[i] = NULL;
	return (dup);
}
