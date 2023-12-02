/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 21:34:07 by atalaver          #+#    #+#             */
/*   Updated: 2023/12/02 23:20:23 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <list>
#include <stdlib.h>
#include <algorithm>

class PmergeMe
{
	private:
		std::vector<int>	vec;
		std::list<int>		lst;
		unsigned			N;

	public:
		PmergeMe();
		PmergeMe( char **argv );
        PmergeMe( const PmergeMe &p );
        const PmergeMe &operator=( const PmergeMe &p );
        ~PmergeMe();

        int get_N();
        void print_data();
        void vector_algorithm();
        void list_algorithm();
};

#endif