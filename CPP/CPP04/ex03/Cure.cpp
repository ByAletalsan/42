/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cure.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 16:49:27 by atalaver          #+#    #+#             */
/*   Updated: 2023/10/22 18:28:53 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cure.hpp"

Cure::Cure() : AMateria()
{
	this->type = "cure";
	std::cout << "Created Cure default!" << std::endl;
}

Cure::Cure( const Cure &i ) : AMateria()
{
	this->type = i.getType();
	std::cout << "Created copy Cure default!" << std::endl;
}

Cure::~Cure()
{
	std::cout << "Destroyed Cure!" << std::endl;
}

Cure& Cure::operator=( const Cure &i )
{
	if (this != &i)
		this->type = i.getType();
	std::cout << "Created (by =) Cure!" << std::endl;
	return (*this);
}

AMateria* Cure::clone() const
{
	return (new Cure(*this));
}

void Cure::use(ICharacter &target)
{
	std::cout << "* heals " << target.getName() << "'s wounds *" << std::endl;
}