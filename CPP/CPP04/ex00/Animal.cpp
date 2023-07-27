/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 07:27:32 by atalaver          #+#    #+#             */
/*   Updated: 2023/07/07 10:39:30 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"

Animal::Animal()
{
    this->type = "";
    std::cout << "Created Animal default" << std::endl;
}

Animal::Animal( const Animal &a )
{
    this->type = a.type;
    std::cout << "Created by copy a Animal " << this->type << std::endl;
}

Animal::~Animal()
{
    std::cout << "Destroyed Animal " << this->type << std::endl;
}

Animal& Animal::operator=( const Animal &a )
{
    if (this != &a)
        this->type = a.type;
    std::cout << "Copy Animal (by = ) " << this->type << std::endl;
    return (*this);
}

const std::string &Animal::getType() const
{
    return (this->type);
}

void Animal::makeSound() const
{
    std::cout << "Sound of a Animal" << std::endl;
}
