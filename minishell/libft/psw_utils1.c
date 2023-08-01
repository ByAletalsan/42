/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   psw_utils1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvasco-m <dvasco-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 20:11:31 by dvasco-m          #+#    #+#             */
/*   Updated: 2023/01/26 20:12:14 by dvasco-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	print_index(t_stl *stack)
{
	ft_printf("\n");
	while (stack != NULL)
	{
		ft_printf("%i \n", stack->pos);
		stack = stack->next;
	}
}

void	index_position(t_stl *stack_a)
{
	t_stl	*nodei;
	t_stl	*nodej;
	int		pos;

	nodei = stack_a;
	while (nodei != NULL)
	{	
		pos = 1;
		nodej = stack_a;
		while (nodej->next != NULL)
		{
			if (nodei->number > nodej->number)
				pos++;
			nodej = nodej->next;
		}
		if (nodei->number > nodej->number)
				pos++;
		nodei->pos = pos;
		nodei = nodei->next;
	}
}

int	is_sort(t_stl *stack_a)
{
	int	sort;
	int	pos;

	sort = 1;
	pos = 1;
	while (stack_a->next != NULL && sort)
	{
		if (stack_a->pos != pos)
			sort = 0;
		pos++;
		stack_a = stack_a->next;
	}
	return (sort);
}

int	evaluate_min(char *number, char *minint, int size, int i)
{
	int	valid;
	int	fin;

	valid = 1;
	fin = 0;
	while (valid && i < size && !fin)
	{
		if (number[i] < *(minint + i))
			fin = 1;
		else if (number[i] > *(minint + i))
			valid = 0;
		i++;
	}
	return (valid);
}

int	evaluate_max(char *number, char *maxint, int size, int i)
{
	int	valid;
	int	fin;

	valid = 1;
	fin = 0;
	while (valid && i < size && !fin)
	{
		if (number[i] < *(maxint + i))
			fin = 1;
		else if (number[i] > *(maxint + i))
			valid = 0;
		i++;
	}
	return (valid);
}
