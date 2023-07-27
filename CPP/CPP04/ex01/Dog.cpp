/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 07:37:05 by atalaver          #+#    #+#             */
/*   Updated: 2023/07/09 08:01:05 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"

Dog::Dog() : Animal()
{
    this->brain = new Brain();
    this->type = "Dog";
    std::cout << "Created a default Dog" << std::endl;
}

Dog::Dog( const Dog &d ) : Animal(d)
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
        *this->brain = *d.brain;
        this->type = d.type;
    }
    std::cout << "Copy Dog (by = ) " << std::endl;
    return (*this);
}

Animal& Dog::operator=( Animal const &a )
{
	if (this != &a)
    {
        *this->brain = *a.getBrain();
        this->type = a.getType();
    }
    std::cout << "Copy Dog (by = ) " << std::endl;
    return (*this);
}

void Dog::makeSound() const
{
    std::cout << "Woof!" << std::endl;
}

Brain* Dog::getBrain() const
{
    return (this->brain);
}
