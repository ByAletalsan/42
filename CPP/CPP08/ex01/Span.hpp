/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 14:06:50 by atalaver          #+#    #+#             */
/*   Updated: 2023/12/02 14:38:56 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPAN_HPP
#define SPAN_HPP

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <algorithm>

class Span
{
	private:
		std::vector<int>	list;
		unsigned int		N;
	public:
		Span();
		Span( unsigned int N );
		Span( const Span &s );
		const Span &operator=( const Span &s );
		~Span();

		void	addNumber( int number );
		void	addNumbers( std::vector<int>::iterator begin, std::vector<int>::iterator end);
		int		shortestSpan() const;
		int		longestSpan() const;


		class ExceptionAddNumber : public std::exception
		{
			public:
       			const char *what() const throw() { return "Error to add number!"; }
		};

		class ExceptionFindRangeInSpan : public std::exception
		{
			public:
       			const char *what() const throw() { return "Error to find range in Span!"; }
		};
};

#endif