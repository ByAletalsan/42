/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Point.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 11:04:03 by atalaver          #+#    #+#             */
/*   Updated: 2023/07/04 12:40:49 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Point.hpp"

Point::Point()
{
    this->x.setRawBits(0);
    this->y.setRawBits(0);
}

Point::Point( const Point &p )
{
    this->x = p.getX();
    this->y = p.getY();
}

Point::Point( const Fixed &x, const Fixed &y )
{
    this->x = x;
    this->y = y;
}

Point::~Point()
{

}

std::ostream& operator<<( std::ostream &out, const Point &p )
{
    out << "(";
    out << p.getX().toFloat();
    out << ", ";
    out << p.getY().toFloat();
    out << ")";
    return (out);
}

Point& Point::operator=( const Point &p )
{
    if (this != &p)
    {
        this->x = p.getX();
        this->y = p.getY();
    }
    return (*this);
}

Fixed  Point::getX() const
{
    return (this->x);
}

Fixed  Point::getY() const
{
    return (this->y);
}
