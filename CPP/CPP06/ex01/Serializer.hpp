/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serializer.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 17:47:18 by atalaver          #+#    #+#             */
/*   Updated: 2023/11/30 18:12:51 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERIALIZER_HPP
#define SERIALIZER_HPP

#include <iostream>
#include <cstdlib> //No aparece en c++98

typedef struct t_Data
{
	std::string	name;
	int			age;
} Data;

//typedef unsigned long int uintptr_t; -> En c++98 no existe este tipo de dato

class Serializer
{
	private:
		Serializer();
		Serializer( const Serializer &s );
		const Serializer &operator=( const Serializer &s );
	public:
		~Serializer();
		static uintptr_t	serialize( Data *ptr );
		static Data*		deserialize( uintptr_t raw );
};

#endif