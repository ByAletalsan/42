/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ice.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 16:39:56 by atalaver          #+#    #+#             */
/*   Updated: 2023/10/22 18:29:12 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Ice.hpp"

Ice::Ice() : AMateria()
{
	this->type = "ice";
	std::cout << "Created Ice default!" << std::endl;
}

Ice::Ice( const Ice &i ) : AMateria()
{
	this->type = i.getType();
	std::cout << "Created copy Ice default!" << std::endl;
}

Ice::~Ice()
{
	std::cout << "Destroyed Ice!" << std::endl;
}

Ice& Ice::operator=( const Ice &i )
{
	if (this != &i)
		this->type = i.getType();
	std::cout << "Created (by =) Ice!" << std::endl;
	return (*this);
}

AMateria* Ice::clone() const
{
	return (new Ice(*this));
}

void Ice::use(ICharacter &target)
{
	std::cout << "* shoots an ice bolt at " << target.getName() << " *" << std::endl;
}
