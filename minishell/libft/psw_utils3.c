/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   psw_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvasco-m <dvasco-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 20:13:43 by dvasco-m          #+#    #+#             */
/*   Updated: 2023/01/30 13:39:52 by dvasco-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_leaks(void)
{
	system("leaks -q push_swap");
}

void	write_error(void)
{
	write(2, "Error\n", 6);
}

void	write_error_free_params(char ***params)
{
	ft_free_params(*params);
	write(2, "Error\n", 6);
}

void	write_error_free_params_stacka(char ***params, t_stl **stack_a)
{
	ft_free_params(*params);
	ft_free_stack(stack_a);
	write(2, "Error\n", 6);
}

void	free_params_stacka(char ***params, t_stl **stack_a)
{
	ft_free_params(*params);
	ft_free_stack(stack_a);
}
