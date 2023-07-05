/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 09:23:03 by atalaver          #+#    #+#             */
/*   Updated: 2023/07/04 10:29:33 by atalaver         ###   ########.fr       */
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

        bool    operator>( const Fixed &f ) const ;
        bool    operator<( const Fixed &f ) const ;
        bool    operator>=( const Fixed &f ) const ;
        bool    operator<=( const Fixed &f ) const ;
        bool    operator==( const Fixed &f ) const ;
        bool    operator!=( const Fixed &f ) const ;

        Fixed   operator+( const Fixed &f ) const ;
        Fixed   operator-( const Fixed &f ) const ;
        Fixed   operator*( const Fixed &f ) const ;
        Fixed   operator/( const Fixed &f ) const ;

        Fixed&  operator++( void );
        Fixed   operator++( int );
        Fixed&  operator--( void );
        Fixed   operator--( int );

        static Fixed& min( Fixed &a, Fixed &b );
        static const Fixed& min( const Fixed &a, const Fixed &b );
        static Fixed& max( Fixed &a, Fixed &b );
        static const Fixed& max( const Fixed &a, const Fixed &b );
};

std::ostream& operator<<( std::ostream &out, const Fixed &f );

#endif
