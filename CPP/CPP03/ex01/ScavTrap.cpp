/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 06:14:21 by atalaver          #+#    #+#             */
/*   Updated: 2023/07/05 06:48:22 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"

ScavTrap::ScavTrap() : ClapTrap()
{
    this->name = "ScavTrap";
    this->hit_points = 100;
    this->energy_points = 50;
    this->attack_damage = 20;
    std::cout << "ScavTrap default created!" << std::endl;
}

ScavTrap::ScavTrap( const ScavTrap &s ) : ClapTrap(s)
{
    std::cout << "ScavTrap copy created!" << std::endl;
}

ScavTrap::ScavTrap( const std::string &name ) : ClapTrap(name)
{
    this->hit_points = 100;
    this->energy_points = 50;
    this->attack_damage = 20;
    std::cout << "ScavTrap " << this->name << " created!" << std::endl;
}

ScavTrap::~ScavTrap()
{
    std::cout << "ScavTrap " << this->name << " destroyed!" << std::endl;
}

ScavTrap&   ScavTrap::operator=( const ScavTrap &s )
{
    if (this != &s)
    {
        this->name = s.getName();
        this->hit_points = s.getHitPoints();
        this->energy_points = s.getEnergyPoints();
        this->attack_damage = s.getAttackDamage();
    }
    std::cout << "ScavTrap copy (by = ) created!" << std::endl;
    return (*this);
}

void ScavTrap::guardGate()
{
    std::cout << "ScavTrap " << this->name << " in Guard Gate Mode!" << std::endl;
}

void ScavTrap::attack( const std::string& target )
{
    if (this->hit_points <= 0)
    {
        std::cout << "Imposible, " << this->name << " is dead!" << std::endl;
        return ;
    }
    if (this->energy_points > 0)
    {
        std::cout << "ScavTrap " << this->name << " attacks " << std::flush;
        std::cout << target << ", causing " << this->attack_damage << " points of damage!" << std::endl;
        this->energy_points--;
    }
    else
        std::cout << "ScavTrap " << this->name << " without energy!" << std::endl;
}

