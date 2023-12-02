/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 21:21:32 by atalaver          #+#    #+#             */
/*   Updated: 2023/11/30 21:27:11 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "iter.hpp"

int	main()
{
	int		numbers[] = { 3, 2, 0, -1, 4 };
	char	caracters[] = { 'a', 'b', 'c', 'd', 'e' };

	std::cout << "Numbers:";
	for (unsigned i = 0; i < 5; i++)
	{
		std::cout << " " << numbers[i];
	}
	std::cout << std::endl;

	std::cout << "Caracters:";
	for (unsigned i = 0; i < 5; i++)
	{
		std::cout << " " << caracters[i];
	}
	std::cout << std::endl;

	std::cout << std::endl;

	std::cout << "ITER NUMBERS +1 !" << std::endl;
	::iter(numbers, 5, sum_1);

	std::cout << "ITER CARACTERS +1 !" << std::endl;
	::iter(caracters, 5, sum_1);

	std::cout << std::endl;

	std::cout << "Numbers:";
	for (unsigned i = 0; i < 5; i++)
	{
		std::cout << " " << numbers[i];
	}
	std::cout << std::endl;

	std::cout << "Caracters:";
	for (unsigned i = 0; i < 5; i++)
	{
		std::cout << " " << caracters[i];
	}
	std::cout << std::endl;

}