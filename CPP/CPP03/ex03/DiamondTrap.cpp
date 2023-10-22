/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DiamondTrap.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 07:45:10 by atalaver          #+#    #+#             */
/*   Updated: 2023/10/22 15:16:59 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DiamondTrap.hpp"

DiamondTrap::DiamondTrap() : FragTrap(), ScavTrap()
{
    this->_name = "DiamondTrap";
    this->ClapTrap::name = name + "_clap_name";
    FragTrap::hit_points = 100;
    ScavTrap::energy_points = 50;
    FragTrap::attack_damage = 30;
    std::cout << "DiamondTrap default created!" << std::endl;
}

DiamondTrap::DiamondTrap( const DiamondTrap &d ) : ClapTrap(d._name), FragTrap(d._name), ScavTrap(d._name)
{
    this->_name = d._name;
    this->ClapTrap::name = name + "_clap_name";
    FragTrap::hit_points = d.FragTrap::hit_points;
    ScavTrap::energy_points = d.ScavTrap::energy_points;
    FragTrap::attack_damage = d.FragTrap::attack_damage;
    std::cout << "DiamondTrap copy created!" << std::endl;
}

DiamondTrap::DiamondTrap( const std::string &name) : FragTrap(name), ScavTrap(name)
{
    this->_name = name;
    this->ClapTrap::name = name + "_clap_name";
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
        this->ClapTrap::name = name + "_clap_name";
        FragTrap::hit_points = d.FragTrap::hit_points;
        ScavTrap::energy_points = d.ScavTrap::energy_points;
        FragTrap::attack_damage = d.FragTrap::attack_damage;
    }
    std::cout << "DiamondTrap copy (by = ) created!" << std::endl;
    return (*this);
}

void    DiamondTrap::whoAmI( void )
{
    std::cout << "I'm a DiamondTrap " << this->_name << ", ClapTrap " << ClapTrap::name << std::endl;
}

void    DiamondTrap::print_stats( void )
{
    std::cout << std::endl;
    std::cout << "Name: " << this->_name << std::endl;
    std::cout << "Hit Points: " << this->hit_points << std::endl;
    std::cout << "Energy Points: " << this->energy_points << std::endl;
    std::cout << "Attack Damage: " << this->attack_damage << std::endl;
    std::cout << std::endl;
}