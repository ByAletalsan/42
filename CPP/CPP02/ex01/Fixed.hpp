/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 09:23:03 by atalaver          #+#    #+#             */
/*   Updated: 2023/07/04 10:23:51 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
#define FIXED_HPP

#include <iostream>
#include <cmath>

class Fixed
{
    private:
        int                 number;
        static const int    bits = 8;

    public:
        Fixed();
        Fixed( const Fixed &f );
        Fixed( const int n );
        Fixed( const float n );
        ~Fixed();
        Fixed& operator=( const Fixed &f );
        int getRawBits( void ) const;
        void setRawBits ( int const raw );
        float toFloat( void ) const;
        int toInt( void ) const;
};

std::ostream& operator<<( std::ostream &out, const Fixed &f );

#endif
