/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 09:28:34 by atalaver          #+#    #+#             */
/*   Updated: 2023/07/05 04:41:13 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Point.hpp"

int main( void )
{
    if ( bsp( Point(), Point(10, 30), Point(20, 0), Point(10, 15) ) )
        std::cout << "IN" << std::endl;
    else
        std::cout << "OUT" << std::endl;

    if ( bsp( Point(-1, 0), Point(0, 1), Point(1, 0), Point(0.5f, 0.5f) ) )
        std::cout << "IN" << std::endl;
    else
        std::cout << "OUT" << std::endl;

    if ( bsp( Point(-1, 0), Point(0, 1), Point(1, 0), Point(2, 0.5f) ) )
        std::cout << "IN" << std::endl;
    else
        std::cout << "OUT" << std::endl;
    
    return (0);
}
