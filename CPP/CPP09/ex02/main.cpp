/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 21:43:22 by atalaver          #+#    #+#             */
/*   Updated: 2023/12/02 23:36:41 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <ctime>
#include <limits.h>

void    parse_arguments( char **argv )
{
	for (unsigned i = 1; argv[i]; i++)
	{
		for (unsigned j = 0; argv[i][j]; j++)
		{
			if (!isdigit(argv[i][j]) || atol(argv[i]) >= INT_MAX || atoi(argv[i]) < 0)
            {
                std::cout << "Arguments error" << std::endl;
                exit(1);
            }
		}
	}
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cout << argv[0] << " <numbers to sort>" << std::endl;
        return 1;
    }

    parse_arguments(argv);
    
    PmergeMe    data(argv);
    data.print_data();

    clock_t start_vector = clock();
    data.vector_algorithm();
    clock_t end_vector = clock();

    clock_t start_list = clock();
    data.list_algorithm();
    clock_t end_list = clock();

    double vector_time = static_cast<double>(end_vector - start_vector) / CLOCKS_PER_SEC;
    double list_time = static_cast<double>(end_list - start_list) / CLOCKS_PER_SEC;

    std::cout << "Time to process a range of " << data.get_N() << " elements with std::vector : " << vector_time * 1000 << " milliseconds" << std::endl;
    std::cout << "Time to process a range of " << data.get_N() << " elements with std::list : " << list_time * 1000 << " milliseconds" << std::endl;

	return 0;
}