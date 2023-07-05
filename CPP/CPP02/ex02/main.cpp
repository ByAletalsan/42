/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 09:28:34 by atalaver          #+#    #+#             */
/*   Updated: 2023/07/04 10:51:40 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

int main( void )
{
    Fixed a;
    Fixed const b( Fixed( 5.05f ) * Fixed( 2 ) );

    std::cout << a << std::endl;
    std::cout << ++a << std::endl;
    std::cout << a << std::endl;
    std::cout << a++ << std::endl;
    std::cout << a << std::endl;
    std::cout << b << std::endl;
    std::cout << Fixed::max( a, b ) << std::endl;
    std::cout << a * b << std::endl;
    std::cout << b / a << std::endl;
    std::cout << Fixed::max( a + 10, b - 1 ) << std::endl;
    a = b;
    if (a == b)
        a++;
    if (a >= b)
        std::cout << --a << " : " << b << std::endl;

    return 0;
}
