/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AAnimal.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 07:27:32 by atalaver          #+#    #+#             */
/*   Updated: 2023/07/09 08:17:28 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AAnimal.hpp"

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

Brain* Animal::getBrain() const
{
    return (NULL);
}