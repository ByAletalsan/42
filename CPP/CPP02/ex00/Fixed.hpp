/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 09:23:03 by atalaver          #+#    #+#             */
/*   Updated: 2023/07/04 10:19:25 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
#define FIXED_HPP

#include <iostream>

class Fixed
{
    private:
        int                 number;
        static const int    bits = 8;

    public:
        Fixed();
        Fixed( const Fixed &f );
        ~Fixed();
        Fixed& operator=( const Fixed &f );
        int getRawBits( void ) const;
        void setRawBits ( int const raw );
};

#endif
