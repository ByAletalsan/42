/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongWrongAnimal.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 10:56:18 by atalaver          #+#    #+#             */
/*   Updated: 2023/07/07 10:56:45 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WrongAnimal.hpp"

WrongAnimal::WrongAnimal()
{
    this->type = "";
    std::cout << "Created WrongAnimal default" << std::endl;
}

WrongAnimal::WrongAnimal( const WrongAnimal &a )
{
    this->type = a.type;
    std::cout << "Created by copy a WrongAnimal " << this->type << std::endl;
}

WrongAnimal::~WrongAnimal()
{
    std::cout << "Destroyed WrongAnimal " << this->type << std::endl;
}

WrongAnimal& WrongAnimal::operator=( const WrongAnimal &a )
{
    if (this != &a)
        this->type = a.type;
    std::cout << "Copy WrongAnimal (by = ) " << this->type << std::endl;
    return (*this);
}

const std::string &WrongAnimal::getType() const
{
    return (this->type);
}

void WrongAnimal::makeSound() const
{
    std::cout << "Sound of a WrongAnimal" << std::endl;
}
