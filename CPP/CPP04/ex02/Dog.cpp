/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 07:37:05 by atalaver          #+#    #+#             */
/*   Updated: 2023/10/22 16:07:38 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"

Dog::Dog() : AAnimal()
{
    this->brain = new Brain();
    this->type = "Dog";
    std::cout << "Created a default Dog" << std::endl;
}

Dog::Dog( const Dog &d ) : AAnimal(d)
{
    this->brain = new Brain( *d.brain );
    this->type = d.type;
    std::cout << "Created by copy a Dog" << std::endl;
}

Dog::~Dog()
{
    delete this->brain;
    std::cout << "Destroyed Dog" << std::endl;
}

Dog& Dog::operator=( const Dog &d )
{
    if (this != &d)
    {
        this->brain = new Brain( *d.brain );
        this->type = d.type;
    }
    std::cout << "Copy Dog (by = ) " << std::endl;
    return (*this);
}

void Dog::makeSound() const
{
    std::cout << "Woof!" << std::endl;
}
