/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funt_aux.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 19:35:41 by asalas-s          #+#    #+#             */
/*   Updated: 2022/07/28 13:23:05 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"structs.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int	ft_atoi(const char *str)
{
	int					i;
	int					sign;
	unsigned long long	result;

	result = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || str[i] == '\r' || str[i] == '\t'
		|| str[i] == '\n' || str[i] == '\v' || str[i] == '\f')
		i++;
	if (str[i] == '-')
		sign *= -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result *= 10;
		result += (str[i] - '0');
		i++;
	}
	return (result * sign);
}

void	ft_print_map(struct s_map map_info)
{
	int	i;
	int	j;

	i = 0;
	while (i < map_info.height)
	{
		j = 0;
		while (j < map_info.width - 1)
		{
			write(1, &map_info.map[i][j], 1);
			j++;
		}
		write(1, "\n", 1);
		i++;
	}
}

int	ft_row_file_len(char *str)
{
	int		file_open;
	char	buffer;
	int		count;
	int		c_r;

	count = 0;
	file_open = open(str, O_RDONLY);
	c_r = read(file_open, &buffer, 1);
	if (buffer < '0' || buffer > '9')
		return (0);
	while (buffer != '\n' && c_r > 0)
	{
		count++;
		c_r = read(file_open, &buffer, 1);
	}
	close(file_open);
	return (count + 1);
}

void	ft_reset(int *i, int *i_f, int *j_f, struct s_square square)
{
	if (*i == *i_f)
	{
		*j_f += 1;
		*i_f += 1;
		*i = square.y_i;
	}
}

void	ft_get_condition(int *num, char *chars, char *str, int file_open)
{
	char	buffer;
	int		len_row;
	int		i;

	buffer = '0';
	*num = 0;
	len_row = ft_row_file_len(str);
	if (len_row < 5)
		return ;
	read(file_open, &buffer, 1);
	i = 0;
	while (i++ < (len_row - 4))
	{
		if (buffer < '0' || buffer > '9')
			return ;
		*num *= 10;
		*num += (buffer - '0');
		read(file_open, &buffer, 1);
	}
	chars[0] = buffer;
	read(file_open, &buffer, 1);
	chars[1] = buffer;
	read(file_open, &buffer, 1);
	chars[2] = buffer;
	read(file_open, &buffer, 1);
}
