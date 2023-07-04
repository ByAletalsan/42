/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 05:28:41 by atalaver          #+#    #+#             */
/*   Updated: 2023/07/04 05:50:26 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HumanA.hpp"

HumanA::HumanA(std::string name, Weapon &weapon)
{
    this->name = name;
    this->weapon = &weapon;
}

const void  HumanA::attack()
{
    if (this->weapon->getType() != "")
    {
        std::cout << this->name << std::flush;
        std::cout << " attacks with their " << std::flush;
        std::cout << this->weapon->getType() << std::endl;
    }
    else
        std::cout << "Don't have a weapon" << std::endl;
}