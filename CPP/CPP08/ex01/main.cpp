/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 14:20:07 by atalaver          #+#    #+#             */
/*   Updated: 2023/12/02 14:49:05 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"

int main()
{
	Span sp = Span(5);
	sp.addNumber(6);
	sp.addNumber(3);
	sp.addNumber(17);
	sp.addNumber(9);
	sp.addNumber(11);
	std::cout << sp.shortestSpan() << std::endl;
	std::cout << sp.longestSpan() << std::endl;

	std::cout << "\nOTROS TEST\n" << std::endl;

	try
	{
		std::vector<int> v;
		v.push_back(1);
		v.push_back(-9);
		v.push_back(3);
		v.push_back(-4);
		v.push_back(15);
		v.push_back(8);
		Span n1(3);
		n1.addNumbers(v.begin(), v.end());
		std::cout << n1.shortestSpan() << std::endl;
		std::cout << n1.longestSpan() << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

	return 0;
}