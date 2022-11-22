/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 11:06:19 by atalaver          #+#    #+#             */
/*   Updated: 2022/11/22 11:23:25 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

char	*ft_read_map(const char	*s)
{
	char	*res;
	char	*str;
	int		f;

	f = open(s, O_RDONLY);
	str = get_next_line(f);
	res = (char *)malloc(1);
	if (!res)
		return (NULL);
	res[0] = '\0';
	while (str)
	{
		res = ft_strjoin(res, str);
		str = get_next_line(f);
	}
	free(str);
	close(f);
	return (res);
}
