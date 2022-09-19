/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   standard_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 17:22:56 by atalaver          #+#    #+#             */
/*   Updated: 2022/07/28 12:50:49 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"structs.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int	ft_row_file_len(char *str);

int	ft_read_number(void)
{
	int		file_open;
	int		len_row;
	int		number;
	int		i;
	char	buffer;

	file_open = open("stdinput.txt", O_RDONLY);
	number = 0;
	len_row = ft_row_file_len("stdinput.txt");
	if (len_row < 5)
		exit (1);
	read(file_open, &buffer, 1);
	i = 0;
	while (i++ < (len_row - 4))
	{
		number *= 10;
		number += (buffer - '0');
		read(file_open, &buffer, 1);
	}
	close(file_open);
	return (number);
}

void	ft_input_file(int number)
{
	int		file_open;
	char	buffer;
	int		count;
	int		i;

	file_open = open("stdinput.txt", O_WRONLY | O_APPEND, 0777);
	read(0, &buffer, 1);
	count = 0;
	i = 1;
	while (number > 0)
	{
		write(file_open, &buffer, 1);
		read(0, &buffer, 1);
		if (++i > count && count != 0)
			return ;
		if (buffer == '\n')
		{
			if (count == 0)
				count = i;
			i = 0;
			number--;
		}
	}
	write(file_open, &buffer, 1);
	close(file_open);
}

void	ft_standard_input(void)
{
	int		file_open;
	char	buffer;
	int		number;

	file_open = open("stdinput.txt", O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (file_open <= 0)
		return ;
	read(0, &buffer, 1);
	if (buffer < '0' || buffer > '9')
		return ;
	while (buffer != '\n')
	{
		write(file_open, &buffer, 1);
		read(0, &buffer, 1);
	}
	write(file_open, &buffer, 1);
	close(file_open);
	number = ft_read_number();
	ft_input_file(number);
	return ;
}
