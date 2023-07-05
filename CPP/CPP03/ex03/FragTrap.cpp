/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 07:18:02 by atalaver          #+#    #+#             */
/*   Updated: 2023/07/05 07:21:51 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FragTrap.hpp"

FragTrap::FragTrap() : ClapTrap()
{
    this->name = "FragTrap";
    this->hit_points = 100;
    this->energy_points = 100;
    this->attack_damage = 30;
    std::cout << "FragTrap default created!" << std::endl;
}

FragTrap::FragTrap( const FragTrap &s ) : ClapTrap(s)
{
    std::cout << "FragTrap copy created!" << std::endl;
}

FragTrap::FragTrap( const std::string &name ) : ClapTrap(name)
{
    this->hit_points = 100;
    this->energy_points = 100;
    this->attack_damage = 30;
    std::cout << "FragTrap " << this->name << " created!" << std::endl;
}

FragTrap::~FragTrap()
{
    std::cout << "FragTrap " << this->name << " destroyed!" << std::endl;
}

FragTrap&   FragTrap::operator=( const FragTrap &s )
{
    if (this != &s)
    {
        this->name = s.getName();
        this->hit_points = s.getHitPoints();
        this->energy_points = s.getEnergyPoints();
        this->attack_damage = s.getAttackDamage();
    }
    std::cout << "FragTrap copy (by = ) created!" << std::endl;
    return (*this);
}

void FragTrap::highFivesGuys(void)
{
    if (this->hit_points <= 0)
    {
        std::cout << "Imposible, " << this->name << " is dead!" << std::endl;
        return ;
    }
    if (this->energy_points > 0)
    {
        std::cout << "FragTrap " << this->name << " high fives!" << std::endl;
        this->energy_points--;
    }
    else
        std::cout << "FragTrap " << this->name << " without energy!" << std::endl;
}
