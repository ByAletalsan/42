/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 10:41:52 by atalaver          #+#    #+#             */
/*   Updated: 2023/07/09 08:01:52 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"

Cat::Cat() : Animal()
{
    this->brain = new Brain();
    this->type = "Cat";
    std::cout << "Created a default Cat" << std::endl;
}

Cat::Cat( const Cat &c ) : Animal(c)
{
    this->brain = new Brain( *c.brain );
    this->type = c.type;
    std::cout << "Created by copy a Cat" << std::endl;
}

Cat::~Cat()
{
    delete this->brain;
    std::cout << "Destroyed Cat" << std::endl;
}

Cat& Cat::operator=( const Cat &c )
{
    if (this != &c)
    {
        *(this->brain) = *(c.getBrain());   
        this->type = c.type;
    }
    std::cout << "Copy Cat (by = ) " << std::endl;
    return (*this);
}

Animal& Cat::operator=( Animal const &a )
{
	if (this != &a)
    {
        *this->brain = *a.getBrain();
        this->type = a.getType();
    }
    std::cout << "Copy Cat (by = ) " << std::endl;
    return (*this);
}

void Cat::makeSound() const
{
    std::cout << "Meow!" << std::endl;
}

Brain* Cat::getBrain() const
{
    return (this->brain);
}