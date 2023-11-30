/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 16:33:09 by atalaver          #+#    #+#             */
/*   Updated: 2023/11/30 17:18:25 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP

#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

class ScalarConverter
{
	private:
		ScalarConverter();
		ScalarConverter( const ScalarConverter &s );
		const ScalarConverter &operator=( const ScalarConverter &s );
	public:
		~ScalarConverter();
		static void	convert( std::string s );
};

#endif