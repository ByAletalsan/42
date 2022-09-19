/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cheks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 21:01:28 by asalas-s          #+#    #+#             */
/*   Updated: 2022/07/28 13:00:31 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"structs.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#include<stdio.h>

int		ft_find_width(int file_open);
int		ft_row_file_len(char *str);
void	ft_get_condition(int *num, char *chars, char *str, int file_open);

int	ft_condition_syntax(int file_open, int row_len)
{
	char	cp[3];
	int		i;

	i = 0;
	read(file_open, &cp[0], 1);
	while (i++ < row_len - 4)
	{
		if (cp[0] < '0' || cp[0] > '9')
			return (1);
		read(file_open, &cp[0], 1);
	}
	if (cp[0] < 32 || cp[0] > 126)
		return (1);
	read(file_open, &cp[1], 1);
	if ((cp[1] < 32 || cp[1] > 126) || (cp[1] == cp[0]))
		return (1);
	read(file_open, &cp[2], 1);
	if (cp[2] < 32 || cp[2] > 126)
		return (1);
	if ((cp[2] == cp[0]) || (cp[2] == cp[1]))
		return (1);
	read(file_open, &cp[0], 1);
	if (cp[0] != '\n')
		return (1);
	return (0);
}

int	ft_cmp_char(int *i, char *buffer, char *cp, int *free_point)
{
	while (buffer[*i] != '\n')
	{
		if (buffer[*i] != cp[0] && buffer[*i] != cp[1])
			return (1);
		if (buffer[*i] == cp[0])
			*free_point = 1;
		*i += 1;
	}
	return (0);
}

int	ft_map_syntax(int file_open, int num, char *cp, int width)
{
	char	*buffer;
	int		i;
	int		free_point;

	i = -1;
	buffer = malloc(width * num);
	read(file_open, buffer, (width * num));
	free_point = 0;
	while (++i < (width * num))
	{
		if (ft_cmp_char(&i, buffer, cp, &free_point) || ((i + 1) % width) != 0)
			return (1);
	}
	if (!free_point)
		return (1);
	return (0);
}

int	ft_check_conditions(int *num, char *cp, int *width, char *str)
{
	int		file_open;

	file_open = open(str, O_RDONLY);
	if (file_open < 0)
		return (0);
	ft_get_condition(num, cp, str, file_open);
	if (*num == 0)
		return (0);
	*width = ft_find_width(file_open);
	if (*width == 0)
		return (0);
	close(file_open);
	return (1);
}

int	ft_check_map(char	*str)
{
	int		file_open;
	int		num;
	char	cp[3];
	int		width;

	if (!ft_check_conditions(&num, cp, &width, str))
	{
		write(1, "map error\n", 10);
		return (0);
	}
	file_open = open(str, O_RDONLY);
	if (ft_condition_syntax(file_open, ft_row_file_len(str)))
	{
		write(1, "map error\n", 10);
		return (0);
	}
	if (ft_map_syntax(file_open, num, cp, width))
	{
		write(1, "map error\n", 10);
		return (0);
	}
	close(file_open);
	return (1);
}
