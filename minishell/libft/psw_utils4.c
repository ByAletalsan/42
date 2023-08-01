/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   psw_utils4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvasco-m <dvasco-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 20:14:23 by dvasco-m          #+#    #+#             */
/*   Updated: 2023/02/08 22:42:03 by dvasco-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_params(char **array_ptr)
{
	int	i;
	int	w;

	i = 0;
	w = 0;
	if (array_ptr != NULL)
	{
		while (array_ptr[w] != NULL)
			w++;
		i = 0;
		while (i < w)
		{
			free (array_ptr[i]);
			i++;
		}
		free(array_ptr);
	}
}

int	size_args(char **argv, int argc)
{
	int	size;
	int	i;
	int	total_size;

	size = 0;
	total_size = 0;
	i = 1;
	while (i < argc)
	{
		size = ft_strlen(argv[i++]);
		if (size == 0)
			return (-1);
		total_size += size;
	}
	total_size += i - 1;
	return (total_size);
}

int	calc_extra_zeros(char *number, t_cnt *ijk)
{
	int	lz;
	int	sign;

	lz = 0;
	sign = 0;
	if (number[ijk->j] == '-')
		sign = 1;
	while (number[lz + sign] == '0')
		lz++;
	return (lz);
}

char	*save_each_number(t_cnt *ijk, char *a_params, char **argv, int *lzeros)
{
	while (argv[ijk->i][ijk->j] != '\0' && ijk->k < ijk->size - 1)
	{
		*lzeros = calc_extra_zeros(argv[ijk->i] + ijk->j, ijk);
		if (argv[ijk->i][ijk->j] == '-')
			a_params[ijk->k++] = argv[ijk->i][ijk->j++];
		while ((argv[ijk->i][ijk->j] != ' ' && argv[ijk->i][ijk->j] != '\0')
			&& ijk->k < ijk->size - 1)
		{
			while (*lzeros > 0)
			{
				ijk->j++;
				*lzeros = *lzeros - 1;
			}
			if (argv[ijk->i][ijk->j] == ' ' || argv[ijk->i][ijk->j] == '\0')
				a_params[ijk->k++] = '0';
			else
				a_params[ijk->k++] = argv[ijk->i][ijk->j++];
		}
		if (argv[ijk->i][ijk->j] == ' ')
			a_params[ijk->k++] = argv[ijk->i][ijk->j++];
	}
	return (a_params);
}

char	*create_array_params(char **argv, int argc, int *lzeros)
{
	char	*array_params;
	t_cnt	ijk;

	ijk.size = size_args(argv, argc);
	if (ijk.size == -1)
		return (NULL);
	array_params = (char *)malloc(ijk.size * sizeof(char));
	if (array_params == NULL)
		return (NULL);
	ijk.i = 1;
	ijk.k = 0;
	while (ijk.i < argc)
	{
		ijk.j = 0;
		array_params = save_each_number(&ijk, array_params, argv, lzeros);
		if (ijk.i++ != argc - 1)
			array_params[ijk.k++] = ' ';
	}
	array_params[ijk.k] = '\0';
	return (array_params);
}
