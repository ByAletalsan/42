/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 12:34:05 by atalaver          #+#    #+#             */
/*   Updated: 2022/07/17 12:35:16 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<unistd.h>

unsigned int	ft_strlen(char *str)
{
	unsigned int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int	ft_errorarg(char *str)
{
	unsigned int	size_str;
	unsigned int	i;

	i = 0;
	size_str = ft_strlen(str);
	if (size_str != 31)
		return (1);
	while (i <= size_str - 1)
	{
		if ((str[i] < '1') || (str[i] > '4'))
			return (2);
		i++;
		if ((str[i] != ' ') && (i < (size_str - 1)))
			return (3);
		i++;
	}
	return (0);
}

int	ft_control_err(int argc, char *str)
{
	unsigned int	err;

	if (argc != 2)
	{
		write(1, "Error\n", 6);
		return (1);
	}
	err = ft_errorarg(str);
	if (err > 0)
	{
		write(1, "Error\n", 6);
		return (1);
	}
	return (0);
}
