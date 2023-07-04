/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 05:41:40 by atalaver          #+#    #+#             */
/*   Updated: 2023/07/04 05:45:17 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HumanB.hpp"

HumanB::HumanB(std::string name)
{
    this->name = name;
    this->weapon = NULL;
}

const void  HumanB::attack()
{
    if (this->weapon)
    {
        std::cout << this->name << std::flush;
        std::cout << " attacks with their " << std::flush;
        std::cout << this->weapon->getType() << std::endl;
    }
    else
        std::cout << "Don't have a weapon" << std::endl;
}

void    HumanB::setWeapon(Weapon &weapon)
{
    this->weapon = &weapon;
}
