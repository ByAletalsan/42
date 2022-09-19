/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 13:48:37 by atalaver          #+#    #+#             */
/*   Updated: 2022/07/15 11:55:21 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdlib.h>

int	ft_find(char *str, char *to_find)
{
	while (*to_find != '\0')
	{
		if (*str != *to_find)
			return (0);
		to_find++;
		str++;
	}
	return (1);
}

char	*ft_strstr(char *str, char *to_find)
{
	int		find;

	find = 0;
	if (*to_find == '\0')
		return (str);
	while (*str != '\0' && find == 0)
	{
		if (*str == *to_find)
		{
			find = ft_find(str, to_find);
		}
		if (find)
			break ;
		str++;
	}
	if (find)
		return (str);
	else
		return (NULL);
}
