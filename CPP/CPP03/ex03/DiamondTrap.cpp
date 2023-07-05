/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DiamondTrap.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 07:45:10 by atalaver          #+#    #+#             */
/*   Updated: 2023/07/05 08:06:21 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DiamondTrap.hpp"

DiamondTrap::DiamondTrap() : ScavTrap(), FragTrap()
{
    this->_name = "DiamondTrap";
    FragTrap::hit_points = 100;
    ScavTrap::energy_points = 50;
    FragTrap::attack_damage = 30;
    std::cout << "DiamondTrap default created!" << std::endl;
}

DiamondTrap::DiamondTrap( const DiamondTrap &d )
{
    this->_name = d._name;
    FragTrap::hit_points = d.FragTrap::hit_points;
    ScavTrap::energy_points = d.ScavTrap::energy_points;
    FragTrap::attack_damage = d.FragTrap::attack_damage;
    std::cout << "DiamondTrap copy created!" << std::endl;
}

DiamondTrap::DiamondTrap( const std::string &name) : ScavTrap(name), FragTrap(name)
{
    this->_name = name;
    FragTrap::hit_points = 100;
    ScavTrap::energy_points = 50;
    FragTrap::attack_damage = 30;
    std::cout << "DiamondTrap " << this->_name << " created!" << std::endl;
}

DiamondTrap::~DiamondTrap()
{
    std::cout << "DiamondTrap " << this->_name << " destroyed!" << std::endl;
}

DiamondTrap& DiamondTrap::operator=( const DiamondTrap &d )
{
    if (this != &d)
    {
        this->_name = d._name;
        FragTrap::hit_points = d.FragTrap::hit_points;
        ScavTrap::energy_points = d.ScavTrap::energy_points;
        FragTrap::attack_damage = d.FragTrap::attack_damage;
    }
    std::cout << "DiamondTrap copy (by = ) created!" << std::endl;
    return (*this);
}

void    DiamondTrap::whoAmI( void )
{
    std::cout << "I'm a DiamondTrap " << this->_name << ", ClapTrap " << FragTrap::name << std::endl;
}
