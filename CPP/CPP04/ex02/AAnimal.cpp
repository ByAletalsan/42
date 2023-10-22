/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AAnimal.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 07:27:32 by atalaver          #+#    #+#             */
/*   Updated: 2023/10/22 16:26:39 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AAnimal.hpp"

AAnimal::~AAnimal()
{
    std::cout << "Destroyed Animal " << this->type << std::endl;
}

AAnimal& AAnimal::operator=( const AAnimal &a )
{
    if (this != &a)
        this->type = a.type;
    std::cout << "Copy Animal (by = ) " << this->type << std::endl;
    return (*this);
}

const std::string &AAnimal::getType() const
{
    return (this->type);
}
