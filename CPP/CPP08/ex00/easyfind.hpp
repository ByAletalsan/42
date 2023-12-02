/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easyfind.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 13:54:40 by atalaver          #+#    #+#             */
/*   Updated: 2023/12/02 14:13:40 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EASYFIND_HPP
#define EASYFIND_HPP

#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <queue>
#include <deque>
#include <stack>
#include <exception>

class except: public std::exception
{
    public:
        const char *what() const throw() { return "Not Found!"; }
};

template <typename T>
typename T::iterator	easyfind( T p1, int p2 )
{
    typename T::iterator	value = std::find(p1.begin(), p1.end(), p2);
    if (value == p1.end())
    	throw except();
    return value;
}

#endif