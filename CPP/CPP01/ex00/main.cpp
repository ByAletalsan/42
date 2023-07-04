/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 07:45:16 by atalaver          #+#    #+#             */
/*   Updated: 2023/07/03 12:38:28 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int main(void)
{

    std::cout << "Creamos un zombie en el stack" << std::endl;
    std::cout << "Zombie name: PEPE" << std::endl;
    Zombie zombi1("PEPE");
    
    std::cout << "Creamos un zombie en el heap" << std::endl;
    std::cout << "Zombie name: PACO" << std::endl;
    Zombie *zombi2 = newZombie("PACO");
    zombi2->announce();
    delete zombi2;

    std::cout << "Llamamos a randomChump" << std::endl;
    randomChump("ELRANDOM");
    zombi1.announce();
    return (0);
}
