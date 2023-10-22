/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 04:59:05 by atalaver          #+#    #+#             */
/*   Updated: 2023/07/05 06:43:35 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

ClapTrap::ClapTrap()
{
    this->name = "ClapTrap";
    this->hit_points = 10;
    this->energy_points = 10;
    this->attack_damage = 0;
    std::cout << "ClapTrap default created!" <<std::endl;
}

ClapTrap::ClapTrap( const ClapTrap &c )
{
    this->name = c.getName();
    this->hit_points = c.getHitPoints();
    this->energy_points = c.getEnergyPoints();
    this->attack_damage = c.getAttackDamage();
    std::cout << "ClapTrap copy created!" << std::endl;
}

ClapTrap::ClapTrap( const std::string &name )
{
    this->name = name;
    this->hit_points = 10;
    this->energy_points = 10;
    this->attack_damage = 0;
    std::cout << "ClapTrap " << this->name << " created!" << std::endl;
}

ClapTrap::~ClapTrap()
{
    std::cout << "ClapTarp " << this->name << " destroyed!" << std::endl;
}

ClapTrap&   ClapTrap::operator=( const ClapTrap &c )
{
    if (this != &c)
    {
        this->name = c.getName();
        this->hit_points = c.getHitPoints();
        this->energy_points = c.getEnergyPoints();
        this->attack_damage = c.getAttackDamage();
    }
    std::cout << "ClapTrap copy (by = ) created!" << std::endl;
    return (*this);
}

void ClapTrap::attack( const std::string& target )
{
    if (this->hit_points <= 0)
    {
        std::cout << "Imposible, " << this->name << " is dead!" << std::endl;
        return ;
    }
    if (this->energy_points > 0)
    {
        std::cout << "ClapTrap " << this->name << " attacks " << std::flush;
        std::cout << target << ", causing " << this->attack_damage << " points of damage!" << std::endl;
        this->energy_points--;
    }
    else
        std::cout << "ClapTrap " << this->name << " without energy!" << std::endl;
}

void ClapTrap::takeDamage( unsigned int amount )
{
    if (this->hit_points <= 0)
    {
        std::cout << "Imposible, " << this->name << " is already dead!" << std::endl;
        return ;
    }
    std::cout << "ClapTrap " << this->name << " takes " << amount << " damage!" << std::endl;
    this->hit_points -= amount;
    if (this->hit_points <= 0)
    {
        std::cout << "ClapTrap " << this->name << " just died!" << std::endl;
        return ;
    }
}

void ClapTrap::beRepaired( unsigned int amount )
{
    if (this->hit_points <= 0)
    {
        std::cout << "Imposible, " << this->name << " is dead!" << std::endl;
        return ;
    }
    if (this->energy_points > 0)
    {
        std::cout << "ClapTrap " << this->name << " repares " << amount << " healt!" << std::endl;
        this->energy_points--;
	this->hit_points += amount;
    }
    else
        std::cout << "ClapTrap " << this->name << " without energy!" << std::endl;
}

void ClapTrap::print_stats() const
{
    std::cout << std::endl;
    std::cout << "Name: " << this->name << std::endl;
    std::cout << "Hit Points: " << this->hit_points << std::endl;
    std::cout << "Energy Points: " << this->energy_points << std::endl;
    std::cout << "Attack Damage: " << this->attack_damage << std::endl;
    std::cout << std::endl;
}

//getters
std::string     ClapTrap::getName() const
{
    return (this->name);
}

int             ClapTrap::getHitPoints() const
{
    return (this->hit_points);
}

int             ClapTrap::getEnergyPoints() const
{
    return (this->energy_points);
}

int             ClapTrap::getAttackDamage() const
{
    return (this->attack_damage);
}
