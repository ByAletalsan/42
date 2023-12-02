/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 13:57:42 by atalaver          #+#    #+#             */
/*   Updated: 2023/12/02 14:13:51 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "easyfind.hpp"

int main()
{
	std::vector<int> vec;
    std::list<int> list;
    std::deque<char> deque;
    
    //VECTOR OF INTEGERS
    for (int i = 0; i < 100; ++i)
    {
        vec.push_back(i);
    }
    try
    {
        std::vector<int>::iterator result;
        result = easyfind(vec, 511);
        std::cout << *result << std::endl;
    }
    catch(std::exception &ex)
    {
        std::cout << ex.what() << std::endl;
    }

    //LIST OF INTEGERS
    for (int i = 0; i < 100; ++i)
    {
        list.push_back(i);
    }
    try
    {
        std::list<int>::iterator result_list;
        result_list = easyfind(list, 42);
        std::cout << *result_list << std::endl;
    }
    catch(std::exception &ex)
    {
        std::cout << ex.what() << std::endl;
    }

    //QUEUE OF CHARS
    for (int i = 33; i < 120; ++i)
    {
        deque.push_back(i);
    }
    try
    {
        std::deque<char>::iterator result_list;
        result_list = easyfind(deque, 'X');
        std::cout << *result_list << std::endl;
    }
    catch(std::exception &ex)
    {
        std::cout << ex.what() << std::endl;
    }
	return 0;
}