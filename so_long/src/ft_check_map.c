/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 10:33:30 by atalaver          #+#    #+#             */
/*   Updated: 2022/12/20 19:19:38 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	ft_check_ber(const char *s)
{
	int	len;

	len = ft_strlen(s);
	if (len < 4)
		return (1);
	if (s[len - 1] != 'r' || s[len - 2] != 'e' || s[len - 3] != 'b'
		|| s[len - 4] != '.')
		return (1);
	return (0);
}

static int	ft_check_rectangular(const char *s)
{
	int	i;
	int	width;
	int	len;

	i = 0;
	while (s[i] != '\0' && s[i] != '\n')
		i++;
	width = i;
	i++;
	len = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\n')
		{
			if (len != width)
				return (1);
			len = -1;
		}
		len++;
		i++;
	}
	if (len != 0 && len != width)
		return (1);
	return (0);
}

static int	ft_fill_elem(int *elem, char c)
{
	if (c == '0')
		elem[0]++;
	else if (c == '1')
		elem[1]++;
	else if (c == 'C')
		elem[2]++;
	else if (c == 'E')
		elem[3]++;
	else if (c == 'P')
		elem[4]++;
	else if (c != '\n')
		return (1);
	return (0);
}

static int	ft_check_elem(const char *s)
{
	int	elem[5];
	int	i;

	i = 0;
	while (i < 5)
		elem[i++] = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (ft_fill_elem(elem, s[i]))
			return (1);
		i++;
	}
	i = 0;
	while (i < 5)
	{
		if (!elem[i])
			return (1);
		i++;
	}
	return (0);
}

int	ft_check_map(t_game game)
{
	if (ft_check_rectangular(game.map.mapa))
		return (1);
	if (ft_check_elem(game.map.mapa))
		return (1);
	if (ft_check_limit(game.map))
		return (1);
	return (0);
}
