/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 09:28:31 by atalaver          #+#    #+#             */
/*   Updated: 2023/07/04 10:19:04 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

Fixed::Fixed()
{
    this->number = 0;
    std::cout << "Default constructor called" << std::endl;
}

Fixed::Fixed( const Fixed &f )
{
    std::cout << "Copy constructor called" << std::endl;
    *this = f;
}

Fixed::Fixed( const int n )
{
    std::cout << "Int constructor called" << std::endl;
    this->number = n << this->bits;
}

Fixed::Fixed( const float n )
{
    std::cout << "Float constructor called" << std::endl;
    this->number = std::roundf(n * (1 << this->bits));
}

Fixed::~Fixed()
{
    std::cout << "Destructor called" << std::endl;
}

Fixed& Fixed::operator=( const Fixed &f )
{
    std::cout << "Assignation operator called" << std::endl;
    if (this != &f)
        this->number = f.getRawBits();
    return (*this);

}
int Fixed::getRawBits( void ) const
{
    return (this->number);
}

void Fixed::setRawBits ( int const raw )
{
    this->number = raw;
}

float Fixed::toFloat( void ) const
{
    return (static_cast<float>(this->number) / (1 << this->bits));
}

int Fixed::toInt( void ) const
{
    return (this->number >> this->bits);
}

std::ostream& operator<<( std::ostream &out, const Fixed &f )
{
    out << f.toFloat();
    return (out);
}
