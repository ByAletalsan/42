/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvasco-m <dvasco-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 20:24:40 by dvasco-m          #+#    #+#             */
/*   Updated: 2023/01/30 13:21:28 by dvasco-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*read_moves(char *array_moves)
{
	char	*aux;
	char	*line;
	int		fin;

	array_moves = (char *)malloc(1);
	array_moves[0] = '\0';
	fin = 0;
	line = NULL;
	while (!fin)
	{	
		aux = array_moves;
		line = get_next_line(0);
		if (line == NULL)
			fin = 1;
		else
			array_moves = ft_strjoin(aux, line);
		if (line != NULL)
			free(line);
		if (aux != NULL && !fin)
			free(aux);
	}
	return (array_moves);
}

int	slct_mve(char *move, t_stack *lstack_a, t_stack *lstack_b, size_t size)
{
	if (ft_strncmp(move, "pa", size) == 0 && size == 2)
		push(&(lstack_b->stack), &(lstack_a->stack), 'd');
	else if (ft_strncmp(move, "pb", size) == 0 && size == 2)
		push(&(lstack_a->stack), &(lstack_b->stack), 'd');
	else if (ft_strncmp(move, "sa", size) == 0 && size == 2)
		swap(&(lstack_a->stack), 'd');
	else if (ft_strncmp(move, "sb", size) == 0 && size == 2)
		swap(&(lstack_b->stack), 'd');
	else if (ft_strncmp(move, "ra", size) == 0 && size == 2)
		rotate(&(lstack_a->stack), 'd');
	else if (ft_strncmp(move, "rb", size) == 0 && size == 2)
		rotate(&(lstack_b->stack), 'd');
	else if (ft_strncmp(move, "rr", size) == 0 && size == 2)
		rrotate(&(lstack_a->stack), &(lstack_b->stack), 1);
	else if (ft_strncmp(move, "rra", size) == 0 && size == 3)
		reverse_rotate(&(lstack_a->stack), 'd');
	else if (ft_strncmp(move, "rrb", size) == 0 && size == 3)
		reverse_rotate(&(lstack_b->stack), 'd');
	else if (ft_strncmp(move, "rrr", size) == 0 && size == 3)
		rreverse_rotate(&(lstack_a->stack), &(lstack_b->stack), 1);
	else
		return (0);
	return (1);
}

void	free_exec_moves(char **movements, t_stl **stack_b)
{
	if (movements != NULL)
		ft_free_params(movements);
	if (*stack_b != NULL)
		ft_free_stack(stack_b);
}

t_stl	*exec_moves(t_stl *stack, int *valid, char *array_moves)
{
	t_stack		lstack_a;
	t_stack		lstack_b;
	char		**movements;
	int			i;
	size_t		size;

	movements = ft_split(array_moves, '\n');
	cre_lstks(&lstack_a, &lstack_b, stack);
	i = 0;
	*valid = 1;
	while (movements[i] != NULL && *valid)
	{
		size = ft_strlen(movements[i]);
		*valid = slct_mve(movements[i++], &lstack_a, &lstack_b, size);
	}
	if (!(*valid))
		write(2, "Error\n", 7);
	else if (is_sort(lstack_a.stack))
		write(1, "OK\n", 3);
	else
		write(1, "KO\n", 3);
	free_exec_moves(movements, &(lstack_b.stack));
	if (array_moves != NULL)
		free(array_moves);
	return (lstack_a.stack);
}

void	ft_leaks2(void)
{
	system("leaks -q checker");
}
