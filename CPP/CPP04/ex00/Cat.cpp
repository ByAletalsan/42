/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 10:41:52 by atalaver          #+#    #+#             */
/*   Updated: 2023/07/07 10:50:05 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"

Cat::Cat() : Animal()
{
    this->type = "Cat";
    std::cout << "Created a default Cat" << std::endl;
}

Cat::Cat( const Cat &c ) : Animal(c)
{
    this->type = c.type;
    std::cout << "Created by copy a Cat" << std::endl;
}

Cat::~Cat()
{
    std::cout << "Destroyed Cat" << std::endl;
}

Cat& Cat::operator=( const Cat &c )
{
    if (this != &c)
        this->type = c.type;
    std::cout << "Copy Cat (by = ) " << std::endl;
    return (*this);
}

void Cat::makeSound() const
{
    std::cout << "Meow!" << std::endl;
}
