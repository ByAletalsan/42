/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 09:28:31 by atalaver          #+#    #+#             */
/*   Updated: 2023/07/04 10:48:09 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

Fixed::Fixed()
{
    this->number = 0;
}

Fixed::Fixed( const Fixed &f )
{
    *this = f;
}

Fixed::Fixed( const int n )
{
    this->number = n << this->bits;
}

Fixed::Fixed( const float n )
{
    this->number = roundf(n * (1 << this->bits));
}

Fixed::~Fixed()
{
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

//OPERATORS

Fixed& Fixed::operator=( const Fixed &f )
{
    if (this != &f)
        this->number = f.getRawBits();
    return (*this);

}

std::ostream& operator<<( std::ostream &out, const Fixed &f )
{
    out << f.toFloat();
    return (out);
}

bool    Fixed::operator>( const Fixed &f ) const
{
    return (this->number > f.getRawBits());
}

bool    Fixed::operator<( const Fixed &f ) const
{
    return (this->number < f.getRawBits());
}

bool    Fixed::operator>=( const Fixed &f ) const
{
    return (this->number >= f.getRawBits());
}

bool    Fixed::operator<=( const Fixed &f ) const
{
    return (this->number <= f.getRawBits());
}

bool    Fixed::operator==( const Fixed &f ) const
{
    return (this->number == f.getRawBits());
}

bool    Fixed::operator!=( const Fixed &f ) const
{
    return (this->number != f.getRawBits());
}

Fixed   Fixed::operator+( const Fixed &f ) const
{
    return (Fixed( this->toFloat() + f.toFloat() ));
}

Fixed   Fixed::operator-( const Fixed &f ) const
{
    return (Fixed( this->toFloat() - f.toFloat() ));
}

Fixed   Fixed::operator*( const Fixed &f ) const
{
    return (Fixed( this->toFloat() * f.toFloat() ));
}

Fixed   Fixed::operator/( const Fixed &f ) const
{
    return (Fixed( this->toFloat() / f.toFloat() ));
}

Fixed&  Fixed::operator++( void )
{
    this->number++;
    return (*this);
}

Fixed   Fixed::operator++( int )
{
    Fixed f( *this );
    f.setRawBits(this->number++);
    return (f);
}

Fixed&  Fixed::operator--( void )
{
    this->number--;
    return (*this);
}

Fixed   Fixed::operator--( int )
{
    Fixed f( *this );
    f.setRawBits(this->number--);
    return (f);
}

//MAX MIN

Fixed& Fixed::min( Fixed &a, Fixed &b )
{
    if (a.getRawBits() < b.getRawBits())
        return (a);
    return (b);
}

const Fixed& Fixed::min( const Fixed &a, const Fixed &b )
{
    if (a.getRawBits() < b.getRawBits())
        return (a);
    return (b);
}

Fixed& Fixed::max( Fixed &a, Fixed &b )
{
    if (a.getRawBits() > b.getRawBits())
        return (a);
    return (b);
}

const Fixed& Fixed::max( const Fixed &a, const Fixed &b )
{
    if (a.getRawBits() > b.getRawBits())
        return (a);
    return (b);
}
