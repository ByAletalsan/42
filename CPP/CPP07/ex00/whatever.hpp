/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whatever.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 21:07:50 by atalaver          #+#    #+#             */
/*   Updated: 2023/11/30 21:15:22 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WHATEVER_HPP
#define WHATEVER_HPP

#include <iostream>

template <typename T>
void	swap( T &first, T &second)
{
	T	aux = first;
	first = second;
	second = aux;
}

template <typename T>
T	min( T first, T second )
{
	return (first < second)? first : second;
}

template <typename T>
T	max( T first, T second )
{
	return (first > second)? first : second;
}

#endif