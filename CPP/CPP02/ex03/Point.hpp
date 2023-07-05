/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Point.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 10:59:38 by atalaver          #+#    #+#             */
/*   Updated: 2023/07/04 12:40:43 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POINT_HPP
#define POINT_HPP

#include "Fixed.hpp"

class Point
{
    private:
        // const Fixed  x;
        // const Fixed  y;
        Fixed   x;
        Fixed   y;

    public:
        Point();
        Point( const Point &p );
        Point( const Fixed &x, const Fixed &y );
        ~Point();
        Point& operator=( const Point &p );

        Fixed  getX() const;
        Fixed  getY() const;
};

bool bsp( Point const a, Point const b, Point const c, Point const point);
std::ostream& operator<<( std::ostream &out, const Point &p );

#endif
