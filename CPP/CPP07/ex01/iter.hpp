/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 21:17:48 by atalaver          #+#    #+#             */
/*   Updated: 2023/11/30 21:22:57 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITER_HPP
#define ITER_HPP

#include <iostream>

template <typename T>
void	iter(T *array, size_t len, void (*func)(T &a))
{
	for (size_t i = 0; i < len; i++)
	{
		func(array[i]);
	}
}

template <typename T>
void	sum_1(T &n)
{
	n += 1;
}

#endif