/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AMateria.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 16:22:04 by atalaver          #+#    #+#             */
/*   Updated: 2023/10/22 18:26:35 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AMateria.hpp"

AMateria::AMateria()
{
	this->type = "";
	std::cout << "Created AMateria default!" << std::endl;
}

AMateria::AMateria( std::string const &type )
{
	this->type = type;
	std::cout << "Created AMateria:" << this->type << "!" << std::endl;
}

AMateria::AMateria( const AMateria &a )
{
	this->type = a.getType();
	std::cout << "Created copy AMateria:" << this->type << "!" << std::endl;
}

AMateria::~AMateria()
{
	std::cout << "Destroyed AMateria:" << this->type << "!" << std::endl;
}

AMateria& AMateria::operator=( const AMateria &a )
{
	if (this != &a)
		this->type = a.getType();
	std::cout << "Created (by =) AMateria:" << this->type << "!" << std::endl;
	return (*this);
}

std::string const &AMateria::getType() const
{
	return (this->type);
}

void AMateria::use(ICharacter &target)
{
	std::cout << "AMateria " << this->type << " used on " << target.getName() << std::endl;
}
