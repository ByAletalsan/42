/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongWrongCat.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 10:59:31 by atalaver          #+#    #+#             */
/*   Updated: 2023/07/07 10:59:38 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WrongCat.hpp"

WrongCat::WrongCat() : WrongAnimal()
{
    this->brain = new Brain();
    this->type = "WrongCat";
    std::cout << "Created a default WrongCat" << std::endl;
}

WrongCat::WrongCat( const WrongCat &c ) : WrongAnimal(c)
{
    this->brain = new Brain();
    this->type = c.type;
    std::cout << "Created by copy a WrongCat" << std::endl;
}

WrongCat::~WrongCat()
{
    delete this->brain;
    std::cout << "Destroyed WrongCat" << std::endl;
}

WrongCat& WrongCat::operator=( const WrongCat &c )
{
    if (this != &c)
    {
        this->brain = new Brain( *c.brain );   
        this->type = c.type;
    }
    std::cout << "Copy WrongCat (by = ) " << std::endl;
    return (*this);
}

void WrongCat::makeSound() const
{
    std::cout << "Meow!" << std::endl;
}
