/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   psw_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvasco-m <dvasco-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 20:12:36 by dvasco-m          #+#    #+#             */
/*   Updated: 2023/01/26 20:13:08 by dvasco-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	cmp_extremes(int sign, char *number, char *maxint, char *minint)
{
	int		valid;
	int		size;

	valid = 1;
	size = (int)ft_strlen(number);
	if (sign)
		valid = evaluate_min(number, minint, size, 0 + sign);
	else
		valid = evaluate_max(number, maxint, size, 0 + sign);
	return (valid);
}

int	valid_number(char *number)
{
	int	valid;
	int	j;
	int	sign;
	int	size;

	valid = 1;
	sign = 0;
	j = 0;
	size = (int)ft_strlen(number);
	if (number[j] == '-')
		sign += 1;
	if (sign && size == 1)
		return (0);
	while (number[j + sign] >= 48 && number[j + sign] <= 57 && j + sign < size)
		j++;
	if (j + sign != size)
		valid = 0;
	if (valid)
	{	
		if (size > 10 + sign)
			valid = 0;
		else if (size == 10 + sign)
			valid = cmp_extremes(sign, number, "2147483647", "-2147483648");
	}
	return (valid);
}

int	duplicated_number(t_stl *stack_a)
{
	t_stl	*node;
	t_stl	*node_i;
	int		valid;

	valid = 1;
	node = stack_a;
	while (node != NULL && valid)
	{
		if (node->next != NULL)
		{
			node_i = node->next;
			while (node_i != NULL && valid)
			{
				if (node->number == node_i->number)
					valid = 0;
				node_i = node_i->next;
			}
		}
		node = node->next;
	}
	return (valid);
}

t_stl	*create_stack_a(char **params, int *valid, t_stl *stack_a)
{
	t_stl	*node;
	int		i;
	int		total_params;

	total_params = 0;
	while (params[total_params] != NULL)
			total_params += 1;
	i = 0;
	*valid = valid_number(params[i]);
	while (i < total_params && *valid)
	{
		node = ft_new_node(ft_atoi(params[i]));
		if (node == NULL)
		{
			if (stack_a != NULL)
				ft_free_stack(&stack_a);
			return (NULL);
		}
		ft_add_node_back(&stack_a, node);
		if (++i < total_params)
			*valid = valid_number(params[i]);
	}
	index_position(stack_a);
	return (stack_a);
}

void	cre_lstks(t_stack *lstack_a, t_stack *lstack_b, t_stl *stack)
{
	lstack_a->stack = stack;
	lstack_a->ab = 'a';
	lstack_a->size = ft_stacksize(stack);
	lstack_a->min = 1;
	lstack_a->max = lstack_a->size;
	lstack_b->stack = NULL;
	lstack_b->ab = 'b';
	lstack_b->size = 0;
	lstack_a->min = 0;
	lstack_a->max = 0;
}
