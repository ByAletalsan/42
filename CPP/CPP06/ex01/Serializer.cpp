/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serializer.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 17:56:02 by atalaver          #+#    #+#             */
/*   Updated: 2023/11/30 18:11:13 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serializer.hpp"

Serializer::Serializer()
{
}

Serializer::Serializer( const Serializer &s )
{
	(void)s;
}

const Serializer &Serializer::operator=( const Serializer &s )
{
	(void)s;
	return *this;
}

Serializer::~Serializer()
{
}

uintptr_t	Serializer::serialize( Data *ptr )
{
	return reinterpret_cast<uintptr_t>(ptr);
}

Data*		Serializer::deserialize( uintptr_t raw )
{
	return reinterpret_cast<Data*>(raw);
}
